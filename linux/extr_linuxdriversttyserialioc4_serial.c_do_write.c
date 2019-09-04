#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ring_entry {int /*<<< orphan*/ * ring_sc; int /*<<< orphan*/ * ring_data; scalar_t__ ring_allsc; } ;
struct ring {int dummy; } ;
struct ioc4_port {int ip_tx_prod; int ip_flags; int ip_tx_lowat; int ip_sscr; TYPE_1__* ip_serial_regs; int /*<<< orphan*/  ip_port; struct ring* ip_outring; struct hooks* ip_hooks; } ;
struct hooks {int /*<<< orphan*/  intr_tx_mt; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  stpir; int /*<<< orphan*/  sscr; int /*<<< orphan*/  stcir; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IOC4_SSCR_DMA_EN ; 
 int /*<<< orphan*/  IOC4_TXCB_INT_WHEN_DONE ; 
 int /*<<< orphan*/  IOC4_TXCB_VALID ; 
 int LOWAT_WRITTEN ; 
 int PROD_CONS_MASK ; 
 int /*<<< orphan*/  enable_intrs (struct ioc4_port*,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_tx_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int do_write(struct ioc4_port *port, char *buf, int len)
{
	int prod_ptr, cons_ptr, total = 0;
	struct ring *outring;
	struct ring_entry *entry;
	struct hooks *hooks = port->ip_hooks;

	BUG_ON(!(len >= 0));

	prod_ptr = port->ip_tx_prod;
	cons_ptr = readl(&port->ip_serial_regs->stcir) & PROD_CONS_MASK;
	outring = port->ip_outring;

	/* Maintain a 1-entry red-zone.  The ring buffer is full when
	 * (cons - prod) % ring_size is 1.  Rather than do this subtraction
	 * in the body of the loop, I'll do it now.
	 */
	cons_ptr = (cons_ptr - (int)sizeof(struct ring_entry)) & PROD_CONS_MASK;

	/* Stuff the bytes into the output */
	while ((prod_ptr != cons_ptr) && (len > 0)) {
		int xx;

		/* Get 4 bytes (one ring entry) at a time */
		entry = (struct ring_entry *)((caddr_t) outring + prod_ptr);

		/* Invalidate all entries */
		entry->ring_allsc = 0;

		/* Copy in some bytes */
		for (xx = 0; (xx < 4) && (len > 0); xx++) {
			entry->ring_data[xx] = *buf++;
			entry->ring_sc[xx] = IOC4_TXCB_VALID;
			len--;
			total++;
		}

		/* If we are within some small threshold of filling up the
		 * entire ring buffer, we must place an EXPLICIT intr here
		 * to generate a lowat interrupt in case we subsequently
		 * really do fill up the ring and the caller goes to sleep.
		 * No need to place more than one though.
		 */
		if (!(port->ip_flags & LOWAT_WRITTEN) &&
			((cons_ptr - prod_ptr) & PROD_CONS_MASK)
				<= port->ip_tx_lowat
					* (int)sizeof(struct ring_entry)) {
			port->ip_flags |= LOWAT_WRITTEN;
			entry->ring_sc[0] |= IOC4_TXCB_INT_WHEN_DONE;
		}

		/* Go on to next entry */
		prod_ptr += sizeof(struct ring_entry);
		prod_ptr &= PROD_CONS_MASK;
	}

	/* If we sent something, start DMA if necessary */
	if (total > 0 && !(port->ip_sscr & IOC4_SSCR_DMA_EN)) {
		port->ip_sscr |= IOC4_SSCR_DMA_EN;
		writel(port->ip_sscr, &port->ip_serial_regs->sscr);
	}

	/* Store the new producer pointer.  If tx is disabled, we stuff the
	 * data into the ring buffer, but we don't actually start tx.
	 */
	if (!uart_tx_stopped(port->ip_port)) {
		writel(prod_ptr, &port->ip_serial_regs->stpir);

		/* If we are now transmitting, enable tx_mt interrupt so we
		 * can disable DMA if necessary when the tx finishes.
		 */
		if (total > 0)
			enable_intrs(port, hooks->intr_tx_mt);
	}
	port->ip_tx_prod = prod_ptr;
	return total;
}
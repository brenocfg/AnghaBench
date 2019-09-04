#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct channel_t {unsigned char ch_mostat; unsigned char ch_mistat; int /*<<< orphan*/  ch_lock; } ;

/* Variables and functions */
 int ENXIO ; 
 int TIOCM_CD ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_RI ; 
 int TIOCM_RTS ; 
 unsigned char UART_MCR_DTR ; 
 unsigned char UART_MCR_RTS ; 
 unsigned char UART_MSR_CTS ; 
 unsigned char UART_MSR_DCD ; 
 unsigned char UART_MSR_DSR ; 
 unsigned char UART_MSR_RI ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int dgnc_get_mstat(struct channel_t *ch)
{
	unsigned char mstat;
	unsigned long flags;
	int rc;

	if (!ch)
		return -ENXIO;

	spin_lock_irqsave(&ch->ch_lock, flags);

	mstat = ch->ch_mostat | ch->ch_mistat;

	spin_unlock_irqrestore(&ch->ch_lock, flags);

	rc = 0;

	if (mstat & UART_MCR_DTR)
		rc |= TIOCM_DTR;
	if (mstat & UART_MCR_RTS)
		rc |= TIOCM_RTS;
	if (mstat & UART_MSR_CTS)
		rc |= TIOCM_CTS;
	if (mstat & UART_MSR_DSR)
		rc |= TIOCM_DSR;
	if (mstat & UART_MSR_RI)
		rc |= TIOCM_RI;
	if (mstat & UART_MSR_DCD)
		rc |= TIOCM_CD;

	return rc;
}
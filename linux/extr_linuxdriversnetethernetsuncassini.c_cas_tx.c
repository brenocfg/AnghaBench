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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct cas {int* tx_old; scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int N_TX_RINGS ; 
 scalar_t__ REG_TX_COMPN (int) ; 
 int /*<<< orphan*/  cas_tx_ringN (struct cas*,int,int) ; 
 scalar_t__ compwb ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  netif_printk (struct cas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void cas_tx(struct net_device *dev, struct cas *cp,
		   u32 status)
{
        int limit, ring;
#ifdef USE_TX_COMPWB
	u64 compwb = le64_to_cpu(cp->init_block->tx_compwb);
#endif
	netif_printk(cp, intr, KERN_DEBUG, cp->dev,
		     "tx interrupt, status: 0x%x, %llx\n",
		     status, (unsigned long long)compwb);
	/* process all the rings */
	for (ring = 0; ring < N_TX_RINGS; ring++) {
#ifdef USE_TX_COMPWB
		/* use the completion writeback registers */
		limit = (CAS_VAL(TX_COMPWB_MSB, compwb) << 8) |
			CAS_VAL(TX_COMPWB_LSB, compwb);
		compwb = TX_COMPWB_NEXT(compwb);
#else
		limit = readl(cp->regs + REG_TX_COMPN(ring));
#endif
		if (cp->tx_old[ring] != limit)
			cas_tx_ringN(cp, ring, limit);
	}
}
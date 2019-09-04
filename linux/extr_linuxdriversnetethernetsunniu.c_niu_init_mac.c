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
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  niu_enable_rx_mac (struct niu*,int) ; 
 int /*<<< orphan*/  niu_enable_tx_mac (struct niu*,int) ; 
 int niu_init_pcs (struct niu*) ; 
 int /*<<< orphan*/  niu_init_rx_mac (struct niu*) ; 
 int /*<<< orphan*/  niu_init_tx_mac (struct niu*) ; 
 int /*<<< orphan*/  niu_init_xif (struct niu*) ; 
 int niu_reset_rx_mac (struct niu*) ; 
 int niu_reset_tx_mac (struct niu*) ; 

__attribute__((used)) static int niu_init_mac(struct niu *np)
{
	int err;

	niu_init_xif(np);
	err = niu_init_pcs(np);
	if (err)
		return err;

	err = niu_reset_tx_mac(np);
	if (err)
		return err;
	niu_init_tx_mac(np);
	err = niu_reset_rx_mac(np);
	if (err)
		return err;
	niu_init_rx_mac(np);

	/* This looks hookey but the RX MAC reset we just did will
	 * undo some of the state we setup in niu_init_tx_mac() so we
	 * have to call it again.  In particular, the RX MAC reset will
	 * set the XMAC_MAX register back to it's default value.
	 */
	niu_init_tx_mac(np);
	niu_enable_tx_mac(np, 1);

	niu_enable_rx_mac(np, 1);

	return 0;
}
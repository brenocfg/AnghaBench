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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  SET_TX_DESC_FIRST_SEG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LAST_SEG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_OWN (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _rtl_fill_usb_tx_desc(u8 *txdesc)
{
	SET_TX_DESC_OWN(txdesc, 1);
	SET_TX_DESC_LAST_SEG(txdesc, 1);
	SET_TX_DESC_FIRST_SEG(txdesc, 1);
}
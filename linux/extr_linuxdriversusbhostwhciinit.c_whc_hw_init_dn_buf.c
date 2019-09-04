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
struct whc {scalar_t__ base; int /*<<< orphan*/  dn_buf_dma; int /*<<< orphan*/  dn_buf; } ;

/* Variables and functions */
 scalar_t__ WUSBDNTSBUFADDR ; 
 int /*<<< orphan*/  le_writeq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void whc_hw_init_dn_buf(struct whc *whc)
{
	/* Clear the Device Notification buffer to ensure the V (valid)
	 * bits are clear.  */
	memset(whc->dn_buf, 0, 4096);

	le_writeq(whc->dn_buf_dma, whc->base + WUSBDNTSBUFADDR);
}
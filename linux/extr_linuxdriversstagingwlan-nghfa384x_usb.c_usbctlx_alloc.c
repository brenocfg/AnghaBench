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
struct hfa384x_usbctlx {int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct hfa384x_usbctlx* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hfa384x_usbctlx *usbctlx_alloc(void)
{
	struct hfa384x_usbctlx *ctlx;

	ctlx = kzalloc(sizeof(*ctlx),
		       in_interrupt() ? GFP_ATOMIC : GFP_KERNEL);
	if (ctlx)
		init_completion(&ctlx->done);

	return ctlx;
}
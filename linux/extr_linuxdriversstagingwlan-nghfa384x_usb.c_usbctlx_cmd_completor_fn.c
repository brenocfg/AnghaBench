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
struct usbctlx_completor {int dummy; } ;
struct usbctlx_cmd_completor {int /*<<< orphan*/  result; int /*<<< orphan*/  cmdresp; } ;

/* Variables and functions */
 int usbctlx_get_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int usbctlx_cmd_completor_fn(struct usbctlx_completor *head)
{
	struct usbctlx_cmd_completor *complete;

	complete = (struct usbctlx_cmd_completor *)head;
	return usbctlx_get_status(complete->cmdresp, complete->result);
}
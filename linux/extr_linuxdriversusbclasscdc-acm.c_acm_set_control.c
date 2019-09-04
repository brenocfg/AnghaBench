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
struct acm {int quirks; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int QUIRK_CONTROL_LINE_STATE ; 
 int /*<<< orphan*/  USB_CDC_REQ_SET_CONTROL_LINE_STATE ; 
 int acm_ctrl_msg (struct acm*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int acm_set_control(struct acm *acm, int control)
{
	if (acm->quirks & QUIRK_CONTROL_LINE_STATE)
		return -EOPNOTSUPP;

	return acm_ctrl_msg(acm, USB_CDC_REQ_SET_CONTROL_LINE_STATE,
			control, NULL, 0);
}
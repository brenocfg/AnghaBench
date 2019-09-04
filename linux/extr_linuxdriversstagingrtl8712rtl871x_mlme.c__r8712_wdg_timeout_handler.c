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
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8712_wdg_wk_cmd (struct _adapter*) ; 

void _r8712_wdg_timeout_handler(struct _adapter *adapter)
{
	r8712_wdg_wk_cmd(adapter);
}
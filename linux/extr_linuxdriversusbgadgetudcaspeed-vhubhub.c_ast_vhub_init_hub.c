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
struct ast_vhub {int /*<<< orphan*/  wake_work; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  ast_vhub_wake_work ; 

void ast_vhub_init_hub(struct ast_vhub *vhub)
{
	vhub->speed = USB_SPEED_UNKNOWN;
	INIT_WORK(&vhub->wake_work, ast_vhub_wake_work);
}
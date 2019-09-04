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
struct uvcg_control_header {int dummy; } ;
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct uvcg_control_header*) ; 
 struct uvcg_control_header* to_uvcg_control_header (struct config_item*) ; 

__attribute__((used)) static void uvcg_control_header_drop(struct config_group *group,
			      struct config_item *item)
{
	struct uvcg_control_header *h = to_uvcg_control_header(item);

	kfree(h);
}
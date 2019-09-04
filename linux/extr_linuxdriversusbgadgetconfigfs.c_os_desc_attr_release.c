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
struct os_desc {int dummy; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct os_desc*) ; 
 struct os_desc* to_os_desc (struct config_item*) ; 

__attribute__((used)) static void os_desc_attr_release(struct config_item *item)
{
	struct os_desc *os_desc = to_os_desc(item);
	kfree(os_desc);
}
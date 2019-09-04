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
struct device_item {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void device_item_free(struct device_item *item)
{
	dstr_free(&item->name);
	dstr_free(&item->value);
}
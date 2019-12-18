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
struct strref {int /*<<< orphan*/  len; int /*<<< orphan*/  array; } ;
struct dstr {int /*<<< orphan*/  array; } ;
struct darray {int dummy; } ;
struct config_item {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstrdup_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  darray_push_back (int,struct darray*,struct config_item*) ; 
 int /*<<< orphan*/  dstr_init_copy_strref (struct dstr*,struct strref*) ; 
 int /*<<< orphan*/  unescape (struct dstr*) ; 

__attribute__((used)) static void config_add_item(struct darray *items, struct strref *name,
			    struct strref *value)
{
	struct config_item item;
	struct dstr item_value;
	dstr_init_copy_strref(&item_value, value);

	unescape(&item_value);

	item.name = bstrdup_n(name->array, name->len);
	item.value = item_value.array;
	darray_push_back(sizeof(struct config_item), items, &item);
}
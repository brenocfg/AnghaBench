#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tb_property_dir {int /*<<< orphan*/  properties; } ;
struct TYPE_2__ {int /*<<< orphan*/  immediate; } ;
struct tb_property {int length; int /*<<< orphan*/  list; TYPE_1__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TB_PROPERTY_TYPE_VALUE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tb_property* tb_property_alloc (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_property_key_valid (char const*) ; 

int tb_property_add_immediate(struct tb_property_dir *parent, const char *key,
			      u32 value)
{
	struct tb_property *property;

	if (!tb_property_key_valid(key))
		return -EINVAL;

	property = tb_property_alloc(key, TB_PROPERTY_TYPE_VALUE);
	if (!property)
		return -ENOMEM;

	property->length = 1;
	property->value.immediate = value;

	list_add_tail(&property->list, &parent->properties);
	return 0;
}
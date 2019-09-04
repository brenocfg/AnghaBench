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
struct TYPE_2__ {struct tb_property* text; struct tb_property* data; int /*<<< orphan*/  dir; } ;
struct tb_property {int type; TYPE_1__ value; } ;

/* Variables and functions */
#define  TB_PROPERTY_TYPE_DATA 130 
#define  TB_PROPERTY_TYPE_DIRECTORY 129 
#define  TB_PROPERTY_TYPE_TEXT 128 
 int /*<<< orphan*/  kfree (struct tb_property*) ; 
 int /*<<< orphan*/  tb_property_free_dir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tb_property_free(struct tb_property *property)
{
	switch (property->type) {
	case TB_PROPERTY_TYPE_DIRECTORY:
		tb_property_free_dir(property->value.dir);
		break;

	case TB_PROPERTY_TYPE_DATA:
		kfree(property->value.data);
		break;

	case TB_PROPERTY_TYPE_TEXT:
		kfree(property->value.text);
		break;

	default:
		break;
	}

	kfree(property);
}
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
struct switch_val {int dummy; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {scalar_t__ type; char* name; struct switch_attr* next; } ;

/* Variables and functions */
 scalar_t__ SWITCH_TYPE_NOVAL ; 
 int /*<<< orphan*/  print_attr_val (struct switch_attr*,struct switch_val*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ swlib_get_attr (struct switch_dev*,struct switch_attr*,struct switch_val*) ; 

__attribute__((used)) static void
show_attrs(struct switch_dev *dev, struct switch_attr *attr, struct switch_val *val)
{
	while (attr) {
		if (attr->type != SWITCH_TYPE_NOVAL) {
			printf("\t%s: ", attr->name);
			if (swlib_get_attr(dev, attr, val) < 0)
				printf("???");
			else
				print_attr_val(attr, val);
			putchar('\n');
		}
		attr = attr->next;
	}
}
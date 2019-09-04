#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  name; } ;
struct TYPE_30__ {TYPE_8__ attr; } ;
struct TYPE_27__ {int /*<<< orphan*/  name; } ;
struct TYPE_28__ {TYPE_6__ attr; } ;
struct TYPE_25__ {int /*<<< orphan*/  name; } ;
struct TYPE_26__ {TYPE_4__ attr; } ;
struct TYPE_23__ {int /*<<< orphan*/  name; } ;
struct TYPE_24__ {TYPE_2__ attr; } ;
struct TYPE_20__ {int /*<<< orphan*/  name; } ;
struct TYPE_22__ {TYPE_14__ attr; } ;
struct TYPE_18__ {int /*<<< orphan*/  name; } ;
struct TYPE_19__ {TYPE_12__ attr; } ;
struct TYPE_16__ {int /*<<< orphan*/  name; } ;
struct TYPE_17__ {TYPE_10__ attr; } ;
struct TYPE_21__ {TYPE_13__ min_time_window_attr; TYPE_11__ max_time_window_attr; TYPE_9__ min_power_attr; TYPE_7__ max_power_attr; TYPE_5__ name_attr; TYPE_3__ time_window_attr; TYPE_1__ power_limit_attr; } ;

/* Variables and functions */
 int MAX_CONSTRAINTS_PER_ZONE ; 
 TYPE_15__* constraint_attrs ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_constraint_attributes(void)
{
	int i;

	for (i = 0; i < MAX_CONSTRAINTS_PER_ZONE; ++i) {
		kfree(constraint_attrs[i].power_limit_attr.attr.name);
		kfree(constraint_attrs[i].time_window_attr.attr.name);
		kfree(constraint_attrs[i].name_attr.attr.name);
		kfree(constraint_attrs[i].max_power_attr.attr.name);
		kfree(constraint_attrs[i].min_power_attr.attr.name);
		kfree(constraint_attrs[i].max_time_window_attr.attr.name);
		kfree(constraint_attrs[i].min_time_window_attr.attr.name);
	}
}
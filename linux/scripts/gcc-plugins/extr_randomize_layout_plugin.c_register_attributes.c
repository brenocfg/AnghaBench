#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; int type_required; int affects_type_identity; void* handler; } ;

/* Variables and functions */
 void* handle_randomize_considered_attr ; 
 void* handle_randomize_layout_attr ; 
 void* handle_randomize_performed_attr ; 
 TYPE_1__ no_randomize_layout_attr ; 
 TYPE_1__ randomize_considered_attr ; 
 TYPE_1__ randomize_layout_attr ; 
 TYPE_1__ randomize_performed_attr ; 
 int /*<<< orphan*/  register_attribute (TYPE_1__*) ; 

__attribute__((used)) static void register_attributes(void *event_data, void *data)
{
	randomize_layout_attr.name		= "randomize_layout";
	randomize_layout_attr.type_required	= true;
	randomize_layout_attr.handler		= handle_randomize_layout_attr;
#if BUILDING_GCC_VERSION >= 4007
	randomize_layout_attr.affects_type_identity = true;
#endif

	no_randomize_layout_attr.name		= "no_randomize_layout";
	no_randomize_layout_attr.type_required	= true;
	no_randomize_layout_attr.handler	= handle_randomize_layout_attr;
#if BUILDING_GCC_VERSION >= 4007
	no_randomize_layout_attr.affects_type_identity = true;
#endif

	randomize_considered_attr.name		= "randomize_considered";
	randomize_considered_attr.type_required	= true;
	randomize_considered_attr.handler	= handle_randomize_considered_attr;

	randomize_performed_attr.name		= "randomize_performed";
	randomize_performed_attr.type_required	= true;
	randomize_performed_attr.handler	= handle_randomize_performed_attr;

	register_attribute(&randomize_layout_attr);
	register_attribute(&no_randomize_layout_attr);
	register_attribute(&randomize_considered_attr);
	register_attribute(&randomize_performed_attr);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; int affects_type_identity; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_user_attribute ; 
 int /*<<< orphan*/  register_attribute (TYPE_1__*) ; 
 TYPE_1__ user_attr ; 

__attribute__((used)) static void register_attributes(void *event_data, void *data)
{
	user_attr.name			= "user";
	user_attr.handler		= handle_user_attribute;
#if BUILDING_GCC_VERSION >= 4007
	user_attr.affects_type_identity	= true;
#endif

	register_attribute(&user_attr);
}
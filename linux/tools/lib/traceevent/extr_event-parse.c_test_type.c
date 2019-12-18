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
typedef  enum tep_event_type { ____Placeholder_tep_event_type } tep_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  do_warning (char*,int,int) ; 

__attribute__((used)) static int test_type(enum tep_event_type type, enum tep_event_type expect)
{
	if (type != expect) {
		do_warning("Error: expected type %d but read %d",
		    expect, type);
		return -1;
	}
	return 0;
}
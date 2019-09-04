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
struct tep_handle {int ref_count; } ;

/* Variables and functions */
 struct tep_handle* calloc (int,int) ; 

struct tep_handle *tep_alloc(void)
{
	struct tep_handle *pevent = calloc(1, sizeof(*pevent));

	if (pevent)
		pevent->ref_count = 1;

	return pevent;
}
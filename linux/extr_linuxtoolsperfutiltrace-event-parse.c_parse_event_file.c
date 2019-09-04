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
struct tep_handle {int dummy; } ;

/* Variables and functions */
 int tep_parse_event (struct tep_handle*,char*,unsigned long,char*) ; 

int parse_event_file(struct tep_handle *pevent,
		     char *buf, unsigned long size, char *sys)
{
	return tep_parse_event(pevent, buf, size, sys);
}
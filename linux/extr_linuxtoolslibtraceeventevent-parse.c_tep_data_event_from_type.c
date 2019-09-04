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
struct event_format {int dummy; } ;

/* Variables and functions */
 struct event_format* tep_find_event (struct tep_handle*,int) ; 

struct event_format *tep_data_event_from_type(struct tep_handle *pevent, int type)
{
	return tep_find_event(pevent, type);
}
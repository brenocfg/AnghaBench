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
struct tep_record {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct tep_handle {int dummy; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_warning (char*,scalar_t__) ; 
 struct event_format* tep_find_event (struct tep_handle*,int) ; 
 int trace_parse_common_type (struct tep_handle*,int /*<<< orphan*/ ) ; 

struct event_format *
tep_find_event_by_record(struct tep_handle *pevent, struct tep_record *record)
{
	int type;

	if (record->size < 0) {
		do_warning("ug! negative record size %d", record->size);
		return NULL;
	}

	type = trace_parse_common_type(pevent, record->data);

	return tep_find_event(pevent, type);
}
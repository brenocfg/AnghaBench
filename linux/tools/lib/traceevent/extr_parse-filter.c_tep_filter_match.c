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
struct tep_record {int dummy; } ;
struct tep_handle {int dummy; } ;
struct tep_filter_type {int /*<<< orphan*/  filter; int /*<<< orphan*/  event; } ;
struct tep_event_filter {int /*<<< orphan*/  filters; struct tep_handle* tep; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int TEP_ERRNO__FILTER_MATCH ; 
 int TEP_ERRNO__FILTER_MISS ; 
 int TEP_ERRNO__FILTER_NOT_FOUND ; 
 int TEP_ERRNO__NO_FILTER ; 
 int /*<<< orphan*/  filter_init_error_buf (struct tep_event_filter*) ; 
 struct tep_filter_type* find_filter_type (struct tep_event_filter*,int) ; 
 int tep_data_type (struct tep_handle*,struct tep_record*) ; 
 int test_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tep_record*,int*) ; 

enum tep_errno tep_filter_match(struct tep_event_filter *filter,
				struct tep_record *record)
{
	struct tep_handle *tep = filter->tep;
	struct tep_filter_type *filter_type;
	int event_id;
	int ret;
	enum tep_errno err = 0;

	filter_init_error_buf(filter);

	if (!filter->filters)
		return TEP_ERRNO__NO_FILTER;

	event_id = tep_data_type(tep, record);

	filter_type = find_filter_type(filter, event_id);
	if (!filter_type)
		return TEP_ERRNO__FILTER_NOT_FOUND;

	ret = test_filter(filter_type->event, filter_type->filter, record, &err);
	if (err)
		return err;

	return ret ? TEP_ERRNO__FILTER_MATCH : TEP_ERRNO__FILTER_MISS;
}
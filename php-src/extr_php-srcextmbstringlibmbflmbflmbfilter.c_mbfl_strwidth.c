#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t len; unsigned char* val; int /*<<< orphan*/  encoding; } ;
typedef  TYPE_1__ mbfl_string ;
struct TYPE_9__ {int /*<<< orphan*/  (* filter_function ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_2__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  filter_count_width ; 
 int /*<<< orphan*/  mbfl_convert_filter_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  mbfl_convert_filter_flush (TYPE_2__*) ; 
 TYPE_2__* mbfl_convert_filter_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  mbfl_encoding_wchar ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

size_t
mbfl_strwidth(mbfl_string *string)
{
	size_t len, n;
	unsigned char *p;
	mbfl_convert_filter *filter;

	len = 0;
	if (string->len > 0 && string->val != NULL) {
		/* wchar filter */
		filter = mbfl_convert_filter_new(
		    string->encoding,
		    &mbfl_encoding_wchar,
		    filter_count_width, 0, &len);
		if (filter == NULL) {
			mbfl_convert_filter_delete(filter);
			return -1;
		}

		/* feed data */
		p = string->val;
		n = string->len;
		while (n > 0) {
			(*filter->filter_function)(*p++, filter);
			n--;
		}

		mbfl_convert_filter_flush(filter);
		mbfl_convert_filter_delete(filter);
	}

	return len;
}
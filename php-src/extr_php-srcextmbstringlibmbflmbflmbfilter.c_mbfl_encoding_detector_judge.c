#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * encoding; int /*<<< orphan*/  flag; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ mbfl_identify_filter ;
struct TYPE_5__ {int filter_list_size; TYPE_1__** filter_list; int /*<<< orphan*/  strict; } ;
typedef  TYPE_2__ mbfl_encoding_detector ;
typedef  int /*<<< orphan*/  mbfl_encoding ;

/* Variables and functions */

const mbfl_encoding *mbfl_encoding_detector_judge(mbfl_encoding_detector *identd)
{
	mbfl_identify_filter *filter;
	const mbfl_encoding *encoding = NULL;
	int n;

	/* judge */
	if (identd != NULL) {
		n = identd->filter_list_size - 1;
		while (n >= 0) {
			filter = identd->filter_list[n];
			if (!filter->flag) {
				if (!identd->strict || !filter->status) {
					encoding = filter->encoding;
				}
			}
			n--;
		}

		/* fallback judge */
		if (!encoding) {
			n = identd->filter_list_size - 1;
			while (n >= 0) {
				filter = identd->filter_list[n];
				if (!filter->flag) {
					encoding = filter->encoding;
				}
				n--;
 			}
		}
	}

	return encoding;
}
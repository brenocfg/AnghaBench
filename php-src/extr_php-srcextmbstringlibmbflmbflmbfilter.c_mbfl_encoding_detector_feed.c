#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char* val; size_t len; } ;
typedef  TYPE_1__ mbfl_string ;
struct TYPE_8__ {scalar_t__ flag; int /*<<< orphan*/  (* filter_function ) (unsigned char,TYPE_2__*) ;} ;
typedef  TYPE_2__ mbfl_identify_filter ;
struct TYPE_9__ {int filter_list_size; TYPE_2__** filter_list; } ;
typedef  TYPE_3__ mbfl_encoding_detector ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (unsigned char,TYPE_2__*) ; 

int
mbfl_encoding_detector_feed(mbfl_encoding_detector *identd, mbfl_string *string)
{
	int res = 0;
	/* feed data */
	if (identd != NULL && string != NULL && string->val != NULL) {
		int num = identd->filter_list_size;
		size_t n = string->len;
		unsigned char *p = string->val;
		int bad = 0;
		while (n > 0) {
			int i;
			for (i = 0; i < num; i++) {
				mbfl_identify_filter *filter = identd->filter_list[i];
				if (!filter->flag) {
					(*filter->filter_function)(*p, filter);
					if (filter->flag) {
						bad++;
					}
				}
			}
			if ((num - 1) <= bad) {
				res = 1;
				break;
			}
			p++;
			n--;
		}
	}

	return res;
}
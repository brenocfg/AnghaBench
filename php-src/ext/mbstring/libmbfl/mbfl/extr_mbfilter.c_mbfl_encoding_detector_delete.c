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
struct TYPE_3__ {int filter_list_size; int /*<<< orphan*/ * filter_list; } ;
typedef  TYPE_1__ mbfl_encoding_detector ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_free (void*) ; 
 int /*<<< orphan*/  mbfl_identify_filter_delete (int /*<<< orphan*/ ) ; 

void
mbfl_encoding_detector_delete(mbfl_encoding_detector *identd)
{
	int i;

	if (identd != NULL) {
		if (identd->filter_list != NULL) {
			i = identd->filter_list_size;
			while (i > 0) {
				i--;
				mbfl_identify_filter_delete(identd->filter_list[i]);
			}
			mbfl_free((void *)identd->filter_list);
		}
		mbfl_free((void *)identd);
	}
}
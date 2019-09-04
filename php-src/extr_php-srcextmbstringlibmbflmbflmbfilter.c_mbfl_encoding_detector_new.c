#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbfl_identify_filter ;
struct TYPE_4__ {int filter_list_size; int strict; int /*<<< orphan*/ ** filter_list; } ;
typedef  TYPE_1__ mbfl_encoding_detector ;
typedef  int /*<<< orphan*/  mbfl_encoding ;

/* Variables and functions */
 scalar_t__ mbfl_calloc (int,int) ; 
 int /*<<< orphan*/  mbfl_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * mbfl_identify_filter_new2 (int /*<<< orphan*/  const*) ; 
 scalar_t__ mbfl_malloc (int) ; 

mbfl_encoding_detector *
mbfl_encoding_detector_new(const mbfl_encoding **elist, int elistsz, int strict)
{
	mbfl_encoding_detector *identd;

	int i, num;
	mbfl_identify_filter *filter;

	if (elist == NULL || elistsz <= 0) {
		return NULL;
	}

	/* allocate */
	identd = (mbfl_encoding_detector*)mbfl_malloc(sizeof(mbfl_encoding_detector));
	if (identd == NULL) {
		return NULL;
	}
	identd->filter_list = (mbfl_identify_filter **)mbfl_calloc(elistsz, sizeof(mbfl_identify_filter *));
	if (identd->filter_list == NULL) {
		mbfl_free(identd);
		return NULL;
	}

	/* create filters */
	i = 0;
	num = 0;
	while (i < elistsz) {
		filter = mbfl_identify_filter_new2(elist[i]);
		if (filter != NULL) {
			identd->filter_list[num] = filter;
			num++;
		}
		i++;
	}
	identd->filter_list_size = num;

	/* set strict flag */
	identd->strict = strict;

	return identd;
}
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
typedef  int TuplesortMethod ;

/* Variables and functions */
#define  SORT_TYPE_EXTERNAL_MERGE 132 
#define  SORT_TYPE_EXTERNAL_SORT 131 
#define  SORT_TYPE_QUICKSORT 130 
#define  SORT_TYPE_STILL_IN_PROGRESS 129 
#define  SORT_TYPE_TOP_N_HEAPSORT 128 

const char *
tuplesort_method_name(TuplesortMethod m)
{
	switch (m)
	{
		case SORT_TYPE_STILL_IN_PROGRESS:
			return "still in progress";
		case SORT_TYPE_TOP_N_HEAPSORT:
			return "top-N heapsort";
		case SORT_TYPE_QUICKSORT:
			return "quicksort";
		case SORT_TYPE_EXTERNAL_SORT:
			return "external sort";
		case SORT_TYPE_EXTERNAL_MERGE:
			return "external merge";
	}

	return "unknown";
}
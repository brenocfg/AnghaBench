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
struct mbfl_identify_vtbl {int encoding; } ;
typedef  enum mbfl_no_encoding { ____Placeholder_mbfl_no_encoding } mbfl_no_encoding ;

/* Variables and functions */
 struct mbfl_identify_vtbl** mbfl_identify_filter_list ; 

const struct mbfl_identify_vtbl * mbfl_identify_filter_get_vtbl(enum mbfl_no_encoding encoding)
{
	const struct mbfl_identify_vtbl * vtbl;
	int i;

	i = 0;
	while ((vtbl = mbfl_identify_filter_list[i++]) != NULL) {
		if (vtbl->encoding == encoding) {
			break;
		}
	}

	return vtbl;
}
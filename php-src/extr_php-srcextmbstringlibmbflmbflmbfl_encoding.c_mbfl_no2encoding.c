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
struct TYPE_4__ {int no_encoding; } ;
typedef  TYPE_1__ mbfl_encoding ;
typedef  enum mbfl_no_encoding { ____Placeholder_mbfl_no_encoding } mbfl_no_encoding ;

/* Variables and functions */
 TYPE_1__** mbfl_encoding_ptr_list ; 

const mbfl_encoding *
mbfl_no2encoding(enum mbfl_no_encoding no_encoding)
{
	const mbfl_encoding *encoding;
	int i;

	i = 0;
	while ((encoding = mbfl_encoding_ptr_list[i++]) != NULL){
		if (encoding->no_encoding == no_encoding) {
			return encoding;
		}
	}

	return NULL;
}
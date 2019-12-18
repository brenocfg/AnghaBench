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
struct TYPE_3__ {int no_encoding; } ;
typedef  TYPE_1__ mbfl_encoding ;
typedef  enum mbfl_no_encoding { ____Placeholder_mbfl_no_encoding } mbfl_no_encoding ;

/* Variables and functions */
 TYPE_1__* mbfl_name2encoding (char const*) ; 
 int mbfl_no_encoding_invalid ; 

enum mbfl_no_encoding
mbfl_name2no_encoding(const char *name)
{
	const mbfl_encoding *encoding;

	encoding = mbfl_name2encoding(name);
	if (encoding == NULL) {
		return mbfl_no_encoding_invalid;
	} else {
		return encoding->no_encoding;
	}
}
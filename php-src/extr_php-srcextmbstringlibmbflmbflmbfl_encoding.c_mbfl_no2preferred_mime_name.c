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
struct TYPE_3__ {char* mime_name; } ;
typedef  TYPE_1__ mbfl_encoding ;
typedef  enum mbfl_no_encoding { ____Placeholder_mbfl_no_encoding } mbfl_no_encoding ;

/* Variables and functions */
 TYPE_1__* mbfl_no2encoding (int) ; 

const char *
mbfl_no2preferred_mime_name(enum mbfl_no_encoding no_encoding)
{
	const mbfl_encoding *encoding;

	encoding = mbfl_no2encoding(no_encoding);
	if (encoding != NULL && encoding->mime_name != NULL && encoding->mime_name[0] != '\0') {
		return encoding->mime_name;
	} else {
		return NULL;
	}
}
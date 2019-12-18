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
struct TYPE_3__ {char const* name; } ;
typedef  TYPE_1__ mbfl_language ;
typedef  enum mbfl_no_language { ____Placeholder_mbfl_no_language } mbfl_no_language ;

/* Variables and functions */
 TYPE_1__* mbfl_no2language (int) ; 

const char *
mbfl_no_language2name(enum mbfl_no_language no_language)
{
	const mbfl_language *language;

	language = mbfl_no2language(no_language);
	if (language == NULL) {
		return "";
	} else {
		return language->name;
	}
}
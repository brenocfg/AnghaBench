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
struct TYPE_3__ {int gmtoffset; int type; } ;
typedef  TYPE_1__ timelib_tz_lookup_table ;
typedef  int timelib_long ;

/* Variables and functions */
 TYPE_1__* abbr_search (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* timelib_calloc (int,int) ; 

__attribute__((used)) static timelib_long timelib_lookup_abbr(char **ptr, int *dst, char **tz_abbr, int *found)
{
	char *word;
	char *begin = *ptr, *end;
	timelib_long  value = 0;
	const timelib_tz_lookup_table *tp;

	while (**ptr != '\0' && **ptr != ')' && **ptr != ' ') {
		++*ptr;
	}
	end = *ptr;
	word = timelib_calloc(1, end - begin + 1);
	memcpy(word, begin, end - begin);

	if ((tp = abbr_search(word, -1, 0))) {
		value = tp->gmtoffset;
		*dst = tp->type;
		value -= tp->type * 3600;
		*found = 1;
	} else {
		*found = 0;
	}

	*tz_abbr = word;
	return value;
}
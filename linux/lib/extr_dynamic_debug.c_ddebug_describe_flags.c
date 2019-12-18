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
struct _ddebug {int flags; } ;
struct TYPE_3__ {int flag; int /*<<< orphan*/  opt_char; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* opt_array ; 

__attribute__((used)) static char *ddebug_describe_flags(struct _ddebug *dp, char *buf,
				    size_t maxlen)
{
	char *p = buf;
	int i;

	BUG_ON(maxlen < 6);
	for (i = 0; i < ARRAY_SIZE(opt_array); ++i)
		if (dp->flags & opt_array[i].flag)
			*p++ = opt_array[i].opt_char;
	if (p == buf)
		*p++ = '_';
	*p = '\0';

	return buf;
}
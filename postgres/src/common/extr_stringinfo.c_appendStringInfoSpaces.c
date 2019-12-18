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
struct TYPE_4__ {char* data; size_t len; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  enlargeStringInfo (TYPE_1__*,int) ; 

void
appendStringInfoSpaces(StringInfo str, int count)
{
	if (count > 0)
	{
		/* Make more room if needed */
		enlargeStringInfo(str, count);

		/* OK, append the spaces */
		while (--count >= 0)
			str->data[str->len++] = ' ';
		str->data[str->len] = '\0';
	}
}
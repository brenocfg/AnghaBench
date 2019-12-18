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
struct TYPE_4__ {char* data; int maxlen; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_1__*) ; 

void
initStringInfo(StringInfo str)
{
	int			size = 1024;	/* initial default buffer size */

	str->data = (char *) palloc(size);
	str->maxlen = size;
	resetStringInfo(str);
}
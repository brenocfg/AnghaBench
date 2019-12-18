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
struct TYPE_4__ {char* data; scalar_t__ len; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 char* oom_buffer ; 

void
resetPQExpBuffer(PQExpBuffer str)
{
	if (str)
	{
		if (str->data != oom_buffer)
		{
			str->len = 0;
			str->data[0] = '\0';
		}
		else
		{
			/* try to reinitialize to valid state */
			initPQExpBuffer(str);
		}
	}
}
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
struct tep_event {int dummy; } ;

/* Variables and functions */
 void event_format__fprintf (struct tep_event*,int,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void event_format__print(struct tep_event *event,
			 int cpu, void *data, int size)
{
	return event_format__fprintf(event, cpu, data, size, stdout);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hist_entry {TYPE_1__* thread; } ;
struct TYPE_2__ {int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 int max (unsigned int,unsigned int) ; 
 int repsep_snprintf (char*,size_t,char*,int /*<<< orphan*/ ,unsigned int,unsigned int,char*) ; 
 char* thread__comm_str (TYPE_1__*) ; 

__attribute__((used)) static int hist_entry__thread_snprintf(struct hist_entry *he, char *bf,
				       size_t size, unsigned int width)
{
	const char *comm = thread__comm_str(he->thread);

	width = max(7U, width) - 8;
	return repsep_snprintf(bf, size, "%7d:%-*.*s", he->thread->tid,
			       width, width, comm ?: "");
}
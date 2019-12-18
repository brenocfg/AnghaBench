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
typedef  scalar_t__ u64 ;
struct timechart {int dummy; } ;
struct per_pidcomm {scalar_t__ start_time; struct io_sample* io_samples; struct per_pidcomm* next; } ;
struct per_pid {struct per_pidcomm* all; struct per_pidcomm* current; } ;
struct io_sample {int type; int fd; struct io_sample* next; scalar_t__ start_time; int /*<<< orphan*/  end_time; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct per_pid* find_create_pid (struct timechart*,int) ; 
 int /*<<< orphan*/  free (struct io_sample*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 void* zalloc (int) ; 

__attribute__((used)) static int pid_begin_io_sample(struct timechart *tchart, int pid, int type,
			       u64 start, int fd)
{
	struct per_pid *p = find_create_pid(tchart, pid);
	struct per_pidcomm *c = p->current;
	struct io_sample *sample;
	struct io_sample *prev;

	if (!c) {
		c = zalloc(sizeof(*c));
		if (!c)
			return -ENOMEM;
		p->current = c;
		c->next = p->all;
		p->all = c;
	}

	prev = c->io_samples;

	if (prev && prev->start_time && !prev->end_time) {
		pr_warning("Skip invalid start event: "
			   "previous event already started!\n");

		/* remove previous event that has been started,
		 * we are not sure we will ever get an end for it */
		c->io_samples = prev->next;
		free(prev);
		return 0;
	}

	sample = zalloc(sizeof(*sample));
	if (!sample)
		return -ENOMEM;
	sample->start_time = start;
	sample->type = type;
	sample->fd = fd;
	sample->next = c->io_samples;
	c->io_samples = sample;

	if (c->start_time == 0 || c->start_time > start)
		c->start_time = start;

	return 0;
}
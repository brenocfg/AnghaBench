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
struct event {int /*<<< orphan*/  result; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct event*) ; 
 int read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 

int event_read(struct event *e)
{
	int rc;

	rc = read(e->fd, &e->result, sizeof(e->result));
	if (rc != sizeof(e->result)) {
		fprintf(stderr, "read error on event %p!\n", e);
		return -1;
	}

	return 0;
}
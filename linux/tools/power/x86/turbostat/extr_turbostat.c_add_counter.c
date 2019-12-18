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
struct msr_counter {unsigned int msr_num; unsigned int width; int type; int format; int flags; struct msr_counter* next; int /*<<< orphan*/  path; int /*<<< orphan*/  name; } ;
typedef  enum counter_type { ____Placeholder_counter_type } counter_type ;
typedef  enum counter_scope { ____Placeholder_counter_scope } counter_scope ;
typedef  enum counter_format { ____Placeholder_counter_format } counter_format ;
struct TYPE_2__ {int added_core_counters; int added_package_counters; struct msr_counter* pp; struct msr_counter* cp; int /*<<< orphan*/  added_thread_counters; struct msr_counter* tp; } ;

/* Variables and functions */
 int MAX_ADDED_COUNTERS ; 
 int /*<<< orphan*/  MAX_ADDED_THREAD_COUNTERS ; 
 int /*<<< orphan*/  NAME_BYTES ; 
 int /*<<< orphan*/  PATH_BYTES ; 
#define  SCOPE_CORE 130 
#define  SCOPE_CPU 129 
#define  SCOPE_PACKAGE 128 
 struct msr_counter* calloc (int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ sys ; 

int add_counter(unsigned int msr_num, char *path, char *name,
	unsigned int width, enum counter_scope scope,
	enum counter_type type, enum counter_format format, int flags)
{
	struct msr_counter *msrp;

	msrp = calloc(1, sizeof(struct msr_counter));
	if (msrp == NULL) {
		perror("calloc");
		exit(1);
	}

	msrp->msr_num = msr_num;
	strncpy(msrp->name, name, NAME_BYTES);
	if (path)
		strncpy(msrp->path, path, PATH_BYTES);
	msrp->width = width;
	msrp->type = type;
	msrp->format = format;
	msrp->flags = flags;

	switch (scope) {

	case SCOPE_CPU:
		msrp->next = sys.tp;
		sys.tp = msrp;
		sys.added_thread_counters++;
		if (sys.added_thread_counters > MAX_ADDED_THREAD_COUNTERS) {
			fprintf(stderr, "exceeded max %d added thread counters\n",
				MAX_ADDED_COUNTERS);
			exit(-1);
		}
		break;

	case SCOPE_CORE:
		msrp->next = sys.cp;
		sys.cp = msrp;
		sys.added_core_counters++;
		if (sys.added_core_counters > MAX_ADDED_COUNTERS) {
			fprintf(stderr, "exceeded max %d added core counters\n",
				MAX_ADDED_COUNTERS);
			exit(-1);
		}
		break;

	case SCOPE_PACKAGE:
		msrp->next = sys.pp;
		sys.pp = msrp;
		sys.added_package_counters++;
		if (sys.added_package_counters > MAX_ADDED_COUNTERS) {
			fprintf(stderr, "exceeded max %d added package counters\n",
				MAX_ADDED_COUNTERS);
			exit(-1);
		}
		break;
	}

	return 0;
}
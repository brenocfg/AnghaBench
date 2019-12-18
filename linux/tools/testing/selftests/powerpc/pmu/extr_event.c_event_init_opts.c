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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int type; int size; int read_format; int /*<<< orphan*/  config; } ;
struct event {char* name; TYPE_1__ attr; } ;

/* Variables and functions */
 int PERF_FORMAT_TOTAL_TIME_ENABLED ; 
 int PERF_FORMAT_TOTAL_TIME_RUNNING ; 
 int /*<<< orphan*/  memset (struct event*,int /*<<< orphan*/ ,int) ; 

void event_init_opts(struct event *e, u64 config, int type, char *name)
{
	memset(e, 0, sizeof(*e));

	e->name = name;

	e->attr.type = type;
	e->attr.config = config;
	e->attr.size = sizeof(e->attr);
	/* This has to match the structure layout in the header */
	e->attr.read_format = PERF_FORMAT_TOTAL_TIME_ENABLED | \
				  PERF_FORMAT_TOTAL_TIME_RUNNING;
}
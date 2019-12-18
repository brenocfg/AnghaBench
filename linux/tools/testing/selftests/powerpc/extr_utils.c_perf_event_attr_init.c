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
struct perf_event_attr {unsigned int type; int size; unsigned long config; int disabled; int exclude_kernel; int exclude_hv; int exclude_guest; int /*<<< orphan*/  read_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_FORMAT_GROUP ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void perf_event_attr_init(struct perf_event_attr *event_attr,
					unsigned int type,
					unsigned long config)
{
	memset(event_attr, 0, sizeof(*event_attr));

	event_attr->type = type;
	event_attr->size = sizeof(struct perf_event_attr);
	event_attr->config = config;
	event_attr->read_format = PERF_FORMAT_GROUP;
	event_attr->disabled = 1;
	event_attr->exclude_kernel = 1;
	event_attr->exclude_hv = 1;
	event_attr->exclude_guest = 1;
}
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
struct TYPE_2__ {size_t nr_namespaces; struct perf_ns_link_info* link_info; void* tid; void* pid; } ;
union perf_event {TYPE_1__ namespaces; } ;
typedef  size_t u64 ;
struct perf_ns_link_info {size_t dev; size_t ino; } ;

/* Variables and functions */
 void* bswap_32 (void*) ; 
 void* bswap_64 (size_t) ; 
 int /*<<< orphan*/  swap_sample_id_all (union perf_event*,struct perf_ns_link_info*) ; 

__attribute__((used)) static void perf_event__namespaces_swap(union perf_event *event,
					bool sample_id_all)
{
	u64 i;

	event->namespaces.pid		= bswap_32(event->namespaces.pid);
	event->namespaces.tid		= bswap_32(event->namespaces.tid);
	event->namespaces.nr_namespaces	= bswap_64(event->namespaces.nr_namespaces);

	for (i = 0; i < event->namespaces.nr_namespaces; i++) {
		struct perf_ns_link_info *ns = &event->namespaces.link_info[i];

		ns->dev = bswap_64(ns->dev);
		ns->ino = bswap_64(ns->ino);
	}

	if (sample_id_all)
		swap_sample_id_all(event, &event->namespaces.link_info[i]);
}
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
typedef  int u64 ;
struct perf_record_namespaces {int nr_namespaces; int /*<<< orphan*/  link_info; } ;
struct perf_ns_link_info {int dummy; } ;
struct namespaces {int end_time; int /*<<< orphan*/  link_info; } ;

/* Variables and functions */
 int NR_NAMESPACES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct namespaces* zalloc (int) ; 

struct namespaces *namespaces__new(struct perf_record_namespaces *event)
{
	struct namespaces *namespaces;
	u64 link_info_size = ((event ? event->nr_namespaces : NR_NAMESPACES) *
			      sizeof(struct perf_ns_link_info));

	namespaces = zalloc(sizeof(struct namespaces) + link_info_size);
	if (!namespaces)
		return NULL;

	namespaces->end_time = -1;

	if (event)
		memcpy(namespaces->link_info, event->link_info, link_info_size);

	return namespaces;
}
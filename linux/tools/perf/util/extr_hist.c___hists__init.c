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
struct perf_hpp_list {int dummy; } ;
struct hists {int socket_filter; int /*<<< orphan*/  hpp_formats; struct perf_hpp_list* hpp_list; int /*<<< orphan*/  lock; void* entries; void* entries_collapsed; void** entries_in_array; void** entries_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* RB_ROOT_CACHED ; 
 int /*<<< orphan*/  memset (struct hists*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int __hists__init(struct hists *hists, struct perf_hpp_list *hpp_list)
{
	memset(hists, 0, sizeof(*hists));
	hists->entries_in_array[0] = hists->entries_in_array[1] = RB_ROOT_CACHED;
	hists->entries_in = &hists->entries_in_array[0];
	hists->entries_collapsed = RB_ROOT_CACHED;
	hists->entries = RB_ROOT_CACHED;
	pthread_mutex_init(&hists->lock, NULL);
	hists->socket_filter = -1;
	hists->hpp_list = hpp_list;
	INIT_LIST_HEAD(&hists->hpp_formats);
	return 0;
}
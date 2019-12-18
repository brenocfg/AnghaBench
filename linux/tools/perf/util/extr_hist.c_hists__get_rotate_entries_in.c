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
struct rb_root_cached {int dummy; } ;
struct hists {int /*<<< orphan*/  lock; struct rb_root_cached* entries_in_array; struct rb_root_cached* entries_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

struct rb_root_cached *hists__get_rotate_entries_in(struct hists *hists)
{
	struct rb_root_cached *root;

	pthread_mutex_lock(&hists->lock);

	root = hists->entries_in;
	if (++hists->entries_in > &hists->entries_in_array[1])
		hists->entries_in = &hists->entries_in_array[0];

	pthread_mutex_unlock(&hists->lock);

	return root;
}
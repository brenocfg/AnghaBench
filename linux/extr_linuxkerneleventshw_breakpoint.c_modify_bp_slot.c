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
typedef  int /*<<< orphan*/  u64 ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 int __modify_bp_slot (struct perf_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_bp_mutex ; 

__attribute__((used)) static int modify_bp_slot(struct perf_event *bp, u64 old_type, u64 new_type)
{
	int ret;

	mutex_lock(&nr_bp_mutex);
	ret = __modify_bp_slot(bp, old_type, new_type);
	mutex_unlock(&nr_bp_mutex);
	return ret;
}
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
struct tc_taprio_sched_entry {int dummy; } ;
struct tc_taprio_qopt_offload {int dummy; } ;
struct __tc_taprio_qopt_offload {struct tc_taprio_qopt_offload offload; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct __tc_taprio_qopt_offload* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct tc_taprio_qopt_offload *taprio_offload_alloc(int num_entries)
{
	size_t size = sizeof(struct tc_taprio_sched_entry) * num_entries +
		      sizeof(struct __tc_taprio_qopt_offload);
	struct __tc_taprio_qopt_offload *__offload;

	__offload = kzalloc(size, GFP_KERNEL);
	if (!__offload)
		return NULL;

	refcount_set(&__offload->users, 1);

	return &__offload->offload;
}
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
struct nfs4_sequence_res {int /*<<< orphan*/ * sr_slot; } ;
struct nfs4_sequence_args {int sa_cache_this; int sa_privileged; int /*<<< orphan*/ * sa_slot; } ;

/* Variables and functions */

void nfs4_init_sequence(struct nfs4_sequence_args *args,
			struct nfs4_sequence_res *res, int cache_reply,
			int privileged)
{
	args->sa_slot = NULL;
	args->sa_cache_this = cache_reply;
	args->sa_privileged = privileged;

	res->sr_slot = NULL;
}
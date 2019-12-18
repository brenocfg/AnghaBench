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
struct rhashtable_compare_arg {struct frag_v4_compare_key* key; } ;
struct inet_frag_queue {int /*<<< orphan*/  key; } ;
struct frag_v4_compare_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,struct frag_v4_compare_key const*,int) ; 

__attribute__((used)) static int ip4_obj_cmpfn(struct rhashtable_compare_arg *arg, const void *ptr)
{
	const struct frag_v4_compare_key *key = arg->key;
	const struct inet_frag_queue *fq = ptr;

	return !!memcmp(&fq->key, key, sizeof(*key));
}
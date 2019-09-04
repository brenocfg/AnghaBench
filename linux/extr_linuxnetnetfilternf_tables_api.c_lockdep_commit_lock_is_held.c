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
struct net {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool lockdep_commit_lock_is_held(struct net *net)
{
#ifdef CONFIG_PROVE_LOCKING
	return lockdep_is_held(&net->nft.commit_mutex);
#else
	return true;
#endif
}
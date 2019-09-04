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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ base_seq; int /*<<< orphan*/  commit_mutex; } ;
struct net {TYPE_1__ nft; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nf_tables_valid_genid(struct net *net, u32 genid)
{
	bool genid_ok;

	mutex_lock(&net->nft.commit_mutex);

	genid_ok = genid == 0 || net->nft.base_seq == genid;
	if (!genid_ok)
		mutex_unlock(&net->nft.commit_mutex);

	/* else, commit mutex has to be released by commit or abort function */
	return genid_ok;
}
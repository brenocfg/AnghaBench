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
struct nf_conntrack_expect {scalar_t__ master; } ;

/* Variables and functions */
 unsigned int NF_CT_EXP_F_SKIP_MASTER ; 

__attribute__((used)) static bool master_matches(const struct nf_conntrack_expect *a,
			   const struct nf_conntrack_expect *b,
			   unsigned int flags)
{
	if (flags & NF_CT_EXP_F_SKIP_MASTER)
		return true;

	return a->master == b->master;
}
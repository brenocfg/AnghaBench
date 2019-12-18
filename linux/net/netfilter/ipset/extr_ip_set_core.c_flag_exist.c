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
typedef  int /*<<< orphan*/  u32 ;
struct nlmsghdr {int nlmsg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSET_FLAG_EXIST ; 
 int NLM_F_EXCL ; 

__attribute__((used)) static inline u32
flag_exist(const struct nlmsghdr *nlh)
{
	return nlh->nlmsg_flags & NLM_F_EXCL ? 0 : IPSET_FLAG_EXIST;
}
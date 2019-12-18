#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct xt_conntrack_mtinfo2 {int /*<<< orphan*/  replsrc_mask; int /*<<< orphan*/  replsrc_addr; } ;
struct nf_conn {TYPE_3__* tuplehash; } ;
struct TYPE_4__ {int /*<<< orphan*/  u3; } ;
struct TYPE_5__ {TYPE_1__ src; } ;
struct TYPE_6__ {TYPE_2__ tuple; } ;

/* Variables and functions */
 size_t IP_CT_DIR_REPLY ; 
 int conntrack_addrcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
conntrack_mt_replsrc(const struct nf_conn *ct,
                     const struct xt_conntrack_mtinfo2 *info,
		     u_int8_t family)
{
	return conntrack_addrcmp(&ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3,
	       &info->replsrc_addr, &info->replsrc_mask, family);
}
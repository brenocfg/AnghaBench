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
typedef  int /*<<< orphan*/  uint64_t ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF_CT_EXT_ACCT ; 
 int /*<<< orphan*/  nf_ct_ext_exist (struct nf_conn const*,int /*<<< orphan*/ ) ; 
 int nla_total_size (int /*<<< orphan*/ ) ; 
 int nla_total_size_64bit (int) ; 

__attribute__((used)) static inline size_t ctnetlink_acct_size(const struct nf_conn *ct)
{
	if (!nf_ct_ext_exist(ct, NF_CT_EXT_ACCT))
		return 0;
	return 2 * nla_total_size(0) /* CTA_COUNTERS_ORIG|REPL */
	       + 2 * nla_total_size_64bit(sizeof(uint64_t)) /* CTA_COUNTERS_PACKETS */
	       + 2 * nla_total_size_64bit(sizeof(uint64_t)) /* CTA_COUNTERS_BYTES */
	       ;
}
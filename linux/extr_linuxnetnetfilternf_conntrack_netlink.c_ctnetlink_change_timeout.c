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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct nlattr {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  status; scalar_t__ timeout; } ;

/* Variables and functions */
 size_t CTA_TIMEOUT ; 
 int ETIME ; 
 scalar_t__ HZ ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  IPS_DYING_BIT ; 
 scalar_t__ nfct_time_stamp ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ctnetlink_change_timeout(struct nf_conn *ct,
				    const struct nlattr * const cda[])
{
	u64 timeout = (u64)ntohl(nla_get_be32(cda[CTA_TIMEOUT])) * HZ;

	if (timeout > INT_MAX)
		timeout = INT_MAX;
	ct->timeout = nfct_time_stamp + (u32)timeout;

	if (test_bit(IPS_DYING_BIT, &ct->status))
		return -ETIME;

	return 0;
}
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
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  status; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_EXPECTED_BIT ; 
 int /*<<< orphan*/  IPS_SEEN_REPLY_BIT ; 
 scalar_t__ IP_CT_DIR_REPLY ; 
 int IP_CT_ESTABLISHED ; 
 int IP_CT_ESTABLISHED_REPLY ; 
 int IP_CT_NEW ; 
 int IP_CT_RELATED ; 
 scalar_t__ NF_CT_DIRECTION (struct nf_conntrack_tuple_hash const*) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash const*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum ip_conntrack_info
ovs_ct_get_info(const struct nf_conntrack_tuple_hash *h)
{
	const struct nf_conn *ct = nf_ct_tuplehash_to_ctrack(h);

	if (NF_CT_DIRECTION(h) == IP_CT_DIR_REPLY)
		return IP_CT_ESTABLISHED_REPLY;
	/* Once we've had two way comms, always ESTABLISHED. */
	if (test_bit(IPS_SEEN_REPLY_BIT, &ct->status))
		return IP_CT_ESTABLISHED;
	if (test_bit(IPS_EXPECTED_BIT, &ct->status))
		return IP_CT_RELATED;
	return IP_CT_NEW;
}
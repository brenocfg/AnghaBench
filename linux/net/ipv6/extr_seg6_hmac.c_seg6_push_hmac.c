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
struct sr6_tlv_hmac {int /*<<< orphan*/  hmac; int /*<<< orphan*/  hmackeyid; } ;
struct seg6_hmac_info {int dummy; } ;
struct net {int dummy; } ;
struct ipv6_sr_hdr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  SEG6_HMAC_FIELD_LEN ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sr6_tlv_hmac* seg6_get_tlv_hmac (struct ipv6_sr_hdr*) ; 
 int seg6_hmac_compute (struct seg6_hmac_info*,struct ipv6_sr_hdr*,struct in6_addr*,int /*<<< orphan*/ ) ; 
 struct seg6_hmac_info* seg6_hmac_info_lookup (struct net*,int /*<<< orphan*/ ) ; 

int seg6_push_hmac(struct net *net, struct in6_addr *saddr,
		   struct ipv6_sr_hdr *srh)
{
	struct seg6_hmac_info *hinfo;
	struct sr6_tlv_hmac *tlv;
	int err = -ENOENT;

	tlv = seg6_get_tlv_hmac(srh);
	if (!tlv)
		return -EINVAL;

	rcu_read_lock();

	hinfo = seg6_hmac_info_lookup(net, be32_to_cpu(tlv->hmackeyid));
	if (!hinfo)
		goto out;

	memset(tlv->hmac, 0, SEG6_HMAC_FIELD_LEN);
	err = seg6_hmac_compute(hinfo, srh, saddr, tlv->hmac);

out:
	rcu_read_unlock();
	return err;
}
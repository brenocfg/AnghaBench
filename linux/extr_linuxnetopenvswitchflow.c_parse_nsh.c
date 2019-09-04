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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int /*<<< orphan*/  mdtype; int /*<<< orphan*/  path_hdr; int /*<<< orphan*/  np; int /*<<< orphan*/  ttl; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  context; TYPE_1__ base; } ;
struct sw_flow_key {TYPE_3__ nsh; } ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  context; } ;
struct nshhdr {TYPE_2__ md1; int /*<<< orphan*/  path_hdr; int /*<<< orphan*/  np; int /*<<< orphan*/  mdtype; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NSH_BASE_HDR_LEN ; 
#define  NSH_M_TYPE1 129 
 scalar_t__ NSH_M_TYPE1_LEN ; 
#define  NSH_M_TYPE2 128 
 int check_header (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nsh_get_flags (struct nshhdr*) ; 
 int /*<<< orphan*/  nsh_get_ttl (struct nshhdr*) ; 
 scalar_t__ nsh_get_ver (struct nshhdr*) ; 
 struct nshhdr* nsh_hdr (struct sk_buff*) ; 
 scalar_t__ nsh_hdr_len (struct nshhdr*) ; 
 unsigned int skb_network_offset (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int parse_nsh(struct sk_buff *skb, struct sw_flow_key *key)
{
	struct nshhdr *nh;
	unsigned int nh_ofs = skb_network_offset(skb);
	u8 version, length;
	int err;

	err = check_header(skb, nh_ofs + NSH_BASE_HDR_LEN);
	if (unlikely(err))
		return err;

	nh = nsh_hdr(skb);
	version = nsh_get_ver(nh);
	length = nsh_hdr_len(nh);

	if (version != 0)
		return -EINVAL;

	err = check_header(skb, nh_ofs + length);
	if (unlikely(err))
		return err;

	nh = nsh_hdr(skb);
	key->nsh.base.flags = nsh_get_flags(nh);
	key->nsh.base.ttl = nsh_get_ttl(nh);
	key->nsh.base.mdtype = nh->mdtype;
	key->nsh.base.np = nh->np;
	key->nsh.base.path_hdr = nh->path_hdr;
	switch (key->nsh.base.mdtype) {
	case NSH_M_TYPE1:
		if (length != NSH_M_TYPE1_LEN)
			return -EINVAL;
		memcpy(key->nsh.context, nh->md1.context,
		       sizeof(nh->md1));
		break;
	case NSH_M_TYPE2:
		memset(key->nsh.context, 0,
		       sizeof(nh->md1));
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
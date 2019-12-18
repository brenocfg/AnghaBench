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
struct seg6_lwt {int /*<<< orphan*/  tuninfo; int /*<<< orphan*/  cache; } ;
struct seg6_iptunnel_encap {int mode; int /*<<< orphan*/  srh; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct lwtunnel_state {int /*<<< orphan*/  headroom; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct ipv6_sr_hdr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 unsigned int AF_INET ; 
 unsigned int AF_INET6 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LWTUNNEL_ENCAP_SEG6 ; 
 int /*<<< orphan*/  LWTUNNEL_STATE_INPUT_REDIRECT ; 
 int /*<<< orphan*/  LWTUNNEL_STATE_OUTPUT_REDIRECT ; 
 int /*<<< orphan*/  SEG6_IPTUNNEL_MAX ; 
 size_t SEG6_IPTUNNEL_SRH ; 
#define  SEG6_IPTUN_MODE_ENCAP 130 
#define  SEG6_IPTUN_MODE_INLINE 129 
#define  SEG6_IPTUN_MODE_L2ENCAP 128 
 int dst_cache_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lwtunnel_state*) ; 
 struct lwtunnel_state* lwtunnel_state_alloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct seg6_iptunnel_encap*,int) ; 
 struct seg6_iptunnel_encap* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  seg6_iptunnel_policy ; 
 int /*<<< orphan*/  seg6_lwt_headroom (struct seg6_iptunnel_encap*) ; 
 struct seg6_lwt* seg6_lwt_lwtunnel (struct lwtunnel_state*) ; 
 int /*<<< orphan*/  seg6_validate_srh (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int seg6_build_state(struct nlattr *nla,
			    unsigned int family, const void *cfg,
			    struct lwtunnel_state **ts,
			    struct netlink_ext_ack *extack)
{
	struct nlattr *tb[SEG6_IPTUNNEL_MAX + 1];
	struct seg6_iptunnel_encap *tuninfo;
	struct lwtunnel_state *newts;
	int tuninfo_len, min_size;
	struct seg6_lwt *slwt;
	int err;

	if (family != AF_INET && family != AF_INET6)
		return -EINVAL;

	err = nla_parse_nested_deprecated(tb, SEG6_IPTUNNEL_MAX, nla,
					  seg6_iptunnel_policy, extack);

	if (err < 0)
		return err;

	if (!tb[SEG6_IPTUNNEL_SRH])
		return -EINVAL;

	tuninfo = nla_data(tb[SEG6_IPTUNNEL_SRH]);
	tuninfo_len = nla_len(tb[SEG6_IPTUNNEL_SRH]);

	/* tuninfo must contain at least the iptunnel encap structure,
	 * the SRH and one segment
	 */
	min_size = sizeof(*tuninfo) + sizeof(struct ipv6_sr_hdr) +
		   sizeof(struct in6_addr);
	if (tuninfo_len < min_size)
		return -EINVAL;

	switch (tuninfo->mode) {
	case SEG6_IPTUN_MODE_INLINE:
		if (family != AF_INET6)
			return -EINVAL;

		break;
	case SEG6_IPTUN_MODE_ENCAP:
		break;
	case SEG6_IPTUN_MODE_L2ENCAP:
		break;
	default:
		return -EINVAL;
	}

	/* verify that SRH is consistent */
	if (!seg6_validate_srh(tuninfo->srh, tuninfo_len - sizeof(*tuninfo)))
		return -EINVAL;

	newts = lwtunnel_state_alloc(tuninfo_len + sizeof(*slwt));
	if (!newts)
		return -ENOMEM;

	slwt = seg6_lwt_lwtunnel(newts);

	err = dst_cache_init(&slwt->cache, GFP_ATOMIC);
	if (err) {
		kfree(newts);
		return err;
	}

	memcpy(&slwt->tuninfo, tuninfo, tuninfo_len);

	newts->type = LWTUNNEL_ENCAP_SEG6;
	newts->flags |= LWTUNNEL_STATE_INPUT_REDIRECT;

	if (tuninfo->mode != SEG6_IPTUN_MODE_L2ENCAP)
		newts->flags |= LWTUNNEL_STATE_OUTPUT_REDIRECT;

	newts->headroom = seg6_lwt_headroom(tuninfo);

	*ts = newts;

	return 0;
}
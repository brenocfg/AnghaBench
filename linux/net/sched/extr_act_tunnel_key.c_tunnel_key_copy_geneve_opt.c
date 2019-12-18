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
typedef  int /*<<< orphan*/  u8 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct geneve_opt {int length; scalar_t__ r3; scalar_t__ r2; scalar_t__ r1; int /*<<< orphan*/  type; int /*<<< orphan*/  opt_class; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 size_t TCA_TUNNEL_KEY_ENC_OPT_GENEVE_CLASS ; 
 size_t TCA_TUNNEL_KEY_ENC_OPT_GENEVE_DATA ; 
 int /*<<< orphan*/  TCA_TUNNEL_KEY_ENC_OPT_GENEVE_MAX ; 
 size_t TCA_TUNNEL_KEY_ENC_OPT_GENEVE_TYPE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  geneve_opt_policy ; 
 int /*<<< orphan*/  memcpy (struct geneve_opt*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

__attribute__((used)) static int
tunnel_key_copy_geneve_opt(const struct nlattr *nla, void *dst, int dst_len,
			   struct netlink_ext_ack *extack)
{
	struct nlattr *tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_MAX + 1];
	int err, data_len, opt_len;
	u8 *data;

	err = nla_parse_nested_deprecated(tb,
					  TCA_TUNNEL_KEY_ENC_OPT_GENEVE_MAX,
					  nla, geneve_opt_policy, extack);
	if (err < 0)
		return err;

	if (!tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_CLASS] ||
	    !tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_TYPE] ||
	    !tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_DATA]) {
		NL_SET_ERR_MSG(extack, "Missing tunnel key geneve option class, type or data");
		return -EINVAL;
	}

	data = nla_data(tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_DATA]);
	data_len = nla_len(tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_DATA]);
	if (data_len < 4) {
		NL_SET_ERR_MSG(extack, "Tunnel key geneve option data is less than 4 bytes long");
		return -ERANGE;
	}
	if (data_len % 4) {
		NL_SET_ERR_MSG(extack, "Tunnel key geneve option data is not a multiple of 4 bytes long");
		return -ERANGE;
	}

	opt_len = sizeof(struct geneve_opt) + data_len;
	if (dst) {
		struct geneve_opt *opt = dst;

		WARN_ON(dst_len < opt_len);

		opt->opt_class =
			nla_get_be16(tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_CLASS]);
		opt->type = nla_get_u8(tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_TYPE]);
		opt->length = data_len / 4; /* length is in units of 4 bytes */
		opt->r1 = 0;
		opt->r2 = 0;
		opt->r3 = 0;

		memcpy(opt + 1, data, data_len);
	}

	return opt_len;
}
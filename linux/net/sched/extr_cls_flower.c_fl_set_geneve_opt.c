#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct geneve_opt {int length; int /*<<< orphan*/  type; int /*<<< orphan*/  opt_class; int /*<<< orphan*/  opt_data; scalar_t__ r3; scalar_t__ r2; scalar_t__ r1; } ;
struct TYPE_2__ {size_t len; int /*<<< orphan*/ * data; } ;
struct fl_flow_key {TYPE_1__ enc_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ERANGE ; 
 int FLOW_DIS_TUN_OPTS_MAX ; 
 int IP_TUNNEL_OPTS_MAX ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 scalar_t__ TCA_FLOWER_KEY_ENC_OPTS_GENEVE ; 
 size_t TCA_FLOWER_KEY_ENC_OPT_GENEVE_CLASS ; 
 size_t TCA_FLOWER_KEY_ENC_OPT_GENEVE_DATA ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_ENC_OPT_GENEVE_MAX ; 
 size_t TCA_FLOWER_KEY_ENC_OPT_GENEVE_TYPE ; 
 int /*<<< orphan*/  geneve_opt_policy ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct geneve_opt*,int,int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 scalar_t__ nla_type (struct nlattr const*) ; 

__attribute__((used)) static int fl_set_geneve_opt(const struct nlattr *nla, struct fl_flow_key *key,
			     int depth, int option_len,
			     struct netlink_ext_ack *extack)
{
	struct nlattr *tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_MAX + 1];
	struct nlattr *class = NULL, *type = NULL, *data = NULL;
	struct geneve_opt *opt;
	int err, data_len = 0;

	if (option_len > sizeof(struct geneve_opt))
		data_len = option_len - sizeof(struct geneve_opt);

	opt = (struct geneve_opt *)&key->enc_opts.data[key->enc_opts.len];
	memset(opt, 0xff, option_len);
	opt->length = data_len / 4;
	opt->r1 = 0;
	opt->r2 = 0;
	opt->r3 = 0;

	/* If no mask has been prodived we assume an exact match. */
	if (!depth)
		return sizeof(struct geneve_opt) + data_len;

	if (nla_type(nla) != TCA_FLOWER_KEY_ENC_OPTS_GENEVE) {
		NL_SET_ERR_MSG(extack, "Non-geneve option type for mask");
		return -EINVAL;
	}

	err = nla_parse_nested_deprecated(tb,
					  TCA_FLOWER_KEY_ENC_OPT_GENEVE_MAX,
					  nla, geneve_opt_policy, extack);
	if (err < 0)
		return err;

	/* We are not allowed to omit any of CLASS, TYPE or DATA
	 * fields from the key.
	 */
	if (!option_len &&
	    (!tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_CLASS] ||
	     !tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_TYPE] ||
	     !tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_DATA])) {
		NL_SET_ERR_MSG(extack, "Missing tunnel key geneve option class, type or data");
		return -EINVAL;
	}

	/* Omitting any of CLASS, TYPE or DATA fields is allowed
	 * for the mask.
	 */
	if (tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_DATA]) {
		int new_len = key->enc_opts.len;

		data = tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_DATA];
		data_len = nla_len(data);
		if (data_len < 4) {
			NL_SET_ERR_MSG(extack, "Tunnel key geneve option data is less than 4 bytes long");
			return -ERANGE;
		}
		if (data_len % 4) {
			NL_SET_ERR_MSG(extack, "Tunnel key geneve option data is not a multiple of 4 bytes long");
			return -ERANGE;
		}

		new_len += sizeof(struct geneve_opt) + data_len;
		BUILD_BUG_ON(FLOW_DIS_TUN_OPTS_MAX != IP_TUNNEL_OPTS_MAX);
		if (new_len > FLOW_DIS_TUN_OPTS_MAX) {
			NL_SET_ERR_MSG(extack, "Tunnel options exceeds max size");
			return -ERANGE;
		}
		opt->length = data_len / 4;
		memcpy(opt->opt_data, nla_data(data), data_len);
	}

	if (tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_CLASS]) {
		class = tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_CLASS];
		opt->opt_class = nla_get_be16(class);
	}

	if (tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_TYPE]) {
		type = tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_TYPE];
		opt->type = nla_get_u8(type);
	}

	return sizeof(struct geneve_opt) + data_len;
}
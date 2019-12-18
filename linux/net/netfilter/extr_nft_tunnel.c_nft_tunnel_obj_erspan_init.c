#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct nlattr {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dir; } ;
struct TYPE_5__ {TYPE_4__ md2; int /*<<< orphan*/  index; } ;
struct TYPE_6__ {int version; TYPE_1__ u; } ;
struct TYPE_7__ {TYPE_2__ erspan; } ;
struct nft_tunnel_opts {int len; int /*<<< orphan*/  flags; TYPE_3__ u; } ;
struct erspan_metadata {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  ERSPAN_VERSION 129 
#define  ERSPAN_VERSION2 128 
 int /*<<< orphan*/  NFTA_TUNNEL_KEY_ERSPAN_MAX ; 
 size_t NFTA_TUNNEL_KEY_ERSPAN_V1_INDEX ; 
 size_t NFTA_TUNNEL_KEY_ERSPAN_V2_DIR ; 
 size_t NFTA_TUNNEL_KEY_ERSPAN_V2_HWID ; 
 size_t NFTA_TUNNEL_KEY_ERSPAN_VERSION ; 
 int /*<<< orphan*/  TUNNEL_ERSPAN_OPT ; 
 int /*<<< orphan*/  nft_tunnel_opts_erspan_policy ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hwid (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_tunnel_obj_erspan_init(const struct nlattr *attr,
				      struct nft_tunnel_opts *opts)
{
	struct nlattr *tb[NFTA_TUNNEL_KEY_ERSPAN_MAX + 1];
	uint8_t hwid, dir;
	int err, version;

	err = nla_parse_nested_deprecated(tb, NFTA_TUNNEL_KEY_ERSPAN_MAX,
					  attr, nft_tunnel_opts_erspan_policy,
					  NULL);
	if (err < 0)
		return err;

	version = ntohl(nla_get_be32(tb[NFTA_TUNNEL_KEY_ERSPAN_VERSION]));
	switch (version) {
	case ERSPAN_VERSION:
		if (!tb[NFTA_TUNNEL_KEY_ERSPAN_V1_INDEX])
			return -EINVAL;

		opts->u.erspan.u.index =
			nla_get_be32(tb[NFTA_TUNNEL_KEY_ERSPAN_V1_INDEX]);
		break;
	case ERSPAN_VERSION2:
		if (!tb[NFTA_TUNNEL_KEY_ERSPAN_V2_DIR] ||
		    !tb[NFTA_TUNNEL_KEY_ERSPAN_V2_HWID])
			return -EINVAL;

		hwid = nla_get_u8(tb[NFTA_TUNNEL_KEY_ERSPAN_V2_HWID]);
		dir = nla_get_u8(tb[NFTA_TUNNEL_KEY_ERSPAN_V2_DIR]);

		set_hwid(&opts->u.erspan.u.md2, hwid);
		opts->u.erspan.u.md2.dir = dir;
		break;
	default:
		return -EOPNOTSUPP;
	}
	opts->u.erspan.version = version;

	opts->len	= sizeof(struct erspan_metadata);
	opts->flags	= TUNNEL_ERSPAN_OPT;

	return 0;
}
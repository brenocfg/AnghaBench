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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  tun_flags; } ;
struct sw_flow_key {int tun_opts_len; TYPE_1__ tun_key; } ;
struct geneve_opt {int length; int type; } ;

/* Variables and functions */
 int EINVAL ; 
 int GENEVE_CRIT_OPT_TYPE ; 
 int /*<<< orphan*/  TUNNEL_CRIT_OPT ; 
 scalar_t__ TUN_METADATA_OPTS (struct sw_flow_key*,int) ; 

__attribute__((used)) static int validate_geneve_opts(struct sw_flow_key *key)
{
	struct geneve_opt *option;
	int opts_len = key->tun_opts_len;
	bool crit_opt = false;

	option = (struct geneve_opt *)TUN_METADATA_OPTS(key, key->tun_opts_len);
	while (opts_len > 0) {
		int len;

		if (opts_len < sizeof(*option))
			return -EINVAL;

		len = sizeof(*option) + option->length * 4;
		if (len > opts_len)
			return -EINVAL;

		crit_opt |= !!(option->type & GENEVE_CRIT_OPT_TYPE);

		option = (struct geneve_opt *)((u8 *)option + len);
		opts_len -= len;
	}

	key->tun_key.tun_flags |= crit_opt ? TUNNEL_CRIT_OPT : 0;

	return 0;
}
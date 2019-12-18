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
typedef  int /*<<< orphan*/  u64 ;
struct sw_flow_match {TYPE_3__* key; } ;
struct nlattr {int dummy; } ;
struct TYPE_4__ {int tci; } ;
struct TYPE_5__ {TYPE_1__ vlan; } ;
struct TYPE_6__ {TYPE_2__ eth; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLAN_CFI_MASK ; 
 int __parse_vlan_from_nlattrs (struct sw_flow_match*,int /*<<< orphan*/ *,int,struct nlattr const**,int,int) ; 
 int htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_vlan_from_nlattrs(struct sw_flow_match *match,
				   u64 *key_attrs, const struct nlattr **a,
				   bool is_mask, bool log)
{
	int err;
	bool encap_valid = false;

	err = __parse_vlan_from_nlattrs(match, key_attrs, false, a,
					is_mask, log);
	if (err)
		return err;

	encap_valid = !!(match->key->eth.vlan.tci & htons(VLAN_CFI_MASK));
	if (encap_valid) {
		err = __parse_vlan_from_nlattrs(match, key_attrs, true, a,
						is_mask, log);
		if (err)
			return err;
	}

	return 0;
}
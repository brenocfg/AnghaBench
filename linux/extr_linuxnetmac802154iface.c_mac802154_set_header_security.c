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
typedef  int /*<<< orphan*/  u8 ;
struct ieee802154_sub_if_data {int /*<<< orphan*/  sec; } ;
struct ieee802154_mac_cb {int /*<<< orphan*/  seclevel; scalar_t__ seclevel_override; scalar_t__ secen; scalar_t__ secen_override; } ;
struct TYPE_6__ {scalar_t__ mode; int /*<<< orphan*/  id; int /*<<< orphan*/  extended_source; int /*<<< orphan*/  short_source; } ;
struct ieee802154_llsec_params {TYPE_3__ out_key; int /*<<< orphan*/  out_level; int /*<<< orphan*/  enabled; } ;
struct TYPE_5__ {scalar_t__ key_id_mode; int /*<<< orphan*/  key_id; int /*<<< orphan*/  extended_src; int /*<<< orphan*/  short_src; int /*<<< orphan*/  level; } ;
struct TYPE_4__ {int security_enabled; } ;
struct ieee802154_hdr {TYPE_2__ sec; TYPE_1__ fc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IEEE802154_SCF_KEY_HW_INDEX ; 
 scalar_t__ IEEE802154_SCF_KEY_SHORT_INDEX ; 
 int /*<<< orphan*/  mac802154_llsec_get_params (int /*<<< orphan*/ *,struct ieee802154_llsec_params*) ; 

__attribute__((used)) static int mac802154_set_header_security(struct ieee802154_sub_if_data *sdata,
					 struct ieee802154_hdr *hdr,
					 const struct ieee802154_mac_cb *cb)
{
	struct ieee802154_llsec_params params;
	u8 level;

	mac802154_llsec_get_params(&sdata->sec, &params);

	if (!params.enabled && cb->secen_override && cb->secen)
		return -EINVAL;
	if (!params.enabled ||
	    (cb->secen_override && !cb->secen) ||
	    !params.out_level)
		return 0;
	if (cb->seclevel_override && !cb->seclevel)
		return -EINVAL;

	level = cb->seclevel_override ? cb->seclevel : params.out_level;

	hdr->fc.security_enabled = 1;
	hdr->sec.level = level;
	hdr->sec.key_id_mode = params.out_key.mode;
	if (params.out_key.mode == IEEE802154_SCF_KEY_SHORT_INDEX)
		hdr->sec.short_src = params.out_key.short_source;
	else if (params.out_key.mode == IEEE802154_SCF_KEY_HW_INDEX)
		hdr->sec.extended_src = params.out_key.extended_source;
	hdr->sec.key_id = params.out_key.id;

	return 0;
}
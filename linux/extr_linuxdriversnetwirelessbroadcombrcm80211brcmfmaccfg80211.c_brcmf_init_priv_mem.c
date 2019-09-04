#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct cfg80211_wowlan_nd_match {int dummy; } ;
struct TYPE_4__ {void* escan_buf; } ;
struct TYPE_3__ {void* nd_info; void* nd; } ;
struct brcmf_cfg80211_info {TYPE_2__ escan_info; TYPE_1__ wowl; void* extra_buf; void* conf; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int BRCMF_ESCAN_BUF_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WL_EXTRA_BUF_MAX ; 
 int /*<<< orphan*/  brcmf_deinit_priv_mem (struct brcmf_cfg80211_info*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 brcmf_init_priv_mem(struct brcmf_cfg80211_info *cfg)
{
	cfg->conf = kzalloc(sizeof(*cfg->conf), GFP_KERNEL);
	if (!cfg->conf)
		goto init_priv_mem_out;
	cfg->extra_buf = kzalloc(WL_EXTRA_BUF_MAX, GFP_KERNEL);
	if (!cfg->extra_buf)
		goto init_priv_mem_out;
	cfg->wowl.nd = kzalloc(sizeof(*cfg->wowl.nd) + sizeof(u32), GFP_KERNEL);
	if (!cfg->wowl.nd)
		goto init_priv_mem_out;
	cfg->wowl.nd_info = kzalloc(sizeof(*cfg->wowl.nd_info) +
				    sizeof(struct cfg80211_wowlan_nd_match *),
				    GFP_KERNEL);
	if (!cfg->wowl.nd_info)
		goto init_priv_mem_out;
	cfg->escan_info.escan_buf = kzalloc(BRCMF_ESCAN_BUF_SIZE, GFP_KERNEL);
	if (!cfg->escan_info.escan_buf)
		goto init_priv_mem_out;

	return 0;

init_priv_mem_out:
	brcmf_deinit_priv_mem(cfg);

	return -ENOMEM;
}
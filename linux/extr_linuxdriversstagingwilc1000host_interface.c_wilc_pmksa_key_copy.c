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
typedef  int u8 ;
struct wilc_vif {int dummy; } ;
struct wid {int size; int /*<<< orphan*/ * val; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int numpmkid; TYPE_1__* pmkidlist; } ;
struct TYPE_6__ {TYPE_2__ pmkid; } ;
struct key_attr {TYPE_3__ attr; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_4__ {int /*<<< orphan*/  pmkid; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PMKID_LEN ; 
 int PMKSA_KEY_LEN ; 
 int /*<<< orphan*/  SET_CFG ; 
 int /*<<< orphan*/  WID_PMKID_INFO ; 
 int /*<<< orphan*/  WID_STR ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wilc_get_vif_idx (struct wilc_vif*) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wilc_pmksa_key_copy(struct wilc_vif *vif, struct key_attr *hif_key)
{
	int i;
	int ret;
	struct wid wid;
	u8 *key_buf;

	key_buf = kmalloc((hif_key->attr.pmkid.numpmkid * PMKSA_KEY_LEN) + 1,
			  GFP_KERNEL);
	if (!key_buf)
		return -ENOMEM;

	key_buf[0] = hif_key->attr.pmkid.numpmkid;

	for (i = 0; i < hif_key->attr.pmkid.numpmkid; i++) {
		memcpy(key_buf + ((PMKSA_KEY_LEN * i) + 1),
		       hif_key->attr.pmkid.pmkidlist[i].bssid, ETH_ALEN);
		memcpy(key_buf + ((PMKSA_KEY_LEN * i) + ETH_ALEN + 1),
		       hif_key->attr.pmkid.pmkidlist[i].pmkid, PMKID_LEN);
	}

	wid.id = WID_PMKID_INFO;
	wid.type = WID_STR;
	wid.val = (s8 *)key_buf;
	wid.size = (hif_key->attr.pmkid.numpmkid * PMKSA_KEY_LEN) + 1;

	ret = wilc_send_config_pkt(vif, SET_CFG, &wid, 1,
				   wilc_get_vif_idx(vif));

	kfree(key_buf);

	return ret;
}
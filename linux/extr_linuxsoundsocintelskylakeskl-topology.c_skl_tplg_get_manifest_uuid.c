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
struct snd_soc_tplg_vendor_uuid_elem {scalar_t__ token; int /*<<< orphan*/  uuid; } ;
struct skl_module {int /*<<< orphan*/  uuid; } ;
struct skl {struct skl_module** modules; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SKL_TKN_UUID ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int skl_tplg_get_manifest_uuid(struct device *dev,
				struct skl *skl,
				struct snd_soc_tplg_vendor_uuid_elem *uuid_tkn)
{
	static int ref_count;
	struct skl_module *mod;

	if (uuid_tkn->token == SKL_TKN_UUID) {
		mod = skl->modules[ref_count];
		memcpy(&mod->uuid, &uuid_tkn->uuid, sizeof(uuid_tkn->uuid));
		ref_count++;
	} else {
		dev_err(dev, "Not an UUID token tkn %d\n", uuid_tkn->token);
		return -EINVAL;
	}

	return 0;
}
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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SKL_TKN_UUID ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  guid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int skl_tplg_get_uuid(struct device *dev, guid_t *guid,
	      struct snd_soc_tplg_vendor_uuid_elem *uuid_tkn)
{
	if (uuid_tkn->token == SKL_TKN_UUID) {
		guid_copy(guid, (guid_t *)&uuid_tkn->uuid);
		return 0;
	}

	dev_err(dev, "Not an UUID token %d\n", uuid_tkn->token);

	return -EINVAL;
}
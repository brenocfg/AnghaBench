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
struct TYPE_3__ {size_t mesh_id_len; int /*<<< orphan*/  mesh_id; } ;
struct TYPE_4__ {TYPE_1__ val; } ;
struct mrvl_mesh_defaults {TYPE_2__ meshie; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 size_t IEEE80211_MAX_SSID_LEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int mesh_get_default_parameters (struct device*,struct mrvl_mesh_defaults*) ; 

__attribute__((used)) static ssize_t mesh_id_get(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	struct mrvl_mesh_defaults defs;
	int ret;

	ret = mesh_get_default_parameters(dev, &defs);

	if (ret)
		return ret;

	if (defs.meshie.val.mesh_id_len > IEEE80211_MAX_SSID_LEN) {
		dev_err(dev, "inconsistent mesh ID length\n");
		defs.meshie.val.mesh_id_len = IEEE80211_MAX_SSID_LEN;
	}

	memcpy(buf, defs.meshie.val.mesh_id, defs.meshie.val.mesh_id_len);
	buf[defs.meshie.val.mesh_id_len] = '\n';
	buf[defs.meshie.val.mesh_id_len + 1] = '\0';

	return defs.meshie.val.mesh_id_len + 1;
}
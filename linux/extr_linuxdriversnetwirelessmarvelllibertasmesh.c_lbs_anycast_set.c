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
typedef  int /*<<< orphan*/  uint32_t ;
struct lbs_private {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cmd_ds_mesh_access {int /*<<< orphan*/ * data; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  mesh_access ;
struct TYPE_2__ {struct lbs_private* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACT_MESH_SET_ANYCAST ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int lbs_mesh_access (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_mesh_access*) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_mesh_access*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 TYPE_1__* to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t lbs_anycast_set(struct device *dev,
		struct device_attribute *attr, const char * buf, size_t count)
{
	struct lbs_private *priv = to_net_dev(dev)->ml_priv;
	struct cmd_ds_mesh_access mesh_access;
	uint32_t datum;
	int ret;

	memset(&mesh_access, 0, sizeof(mesh_access));
	sscanf(buf, "%x", &datum);
	mesh_access.data[0] = cpu_to_le32(datum);

	ret = lbs_mesh_access(priv, CMD_ACT_MESH_SET_ANYCAST, &mesh_access);
	if (ret)
		return ret;

	return strlen(buf);
}
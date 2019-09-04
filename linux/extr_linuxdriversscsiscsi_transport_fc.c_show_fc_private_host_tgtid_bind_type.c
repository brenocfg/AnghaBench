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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FC_BINDTYPE_MAX_NAMELEN ; 
 int /*<<< orphan*/  fc_host_tgtid_bind_type (struct Scsi_Host*) ; 
 char* get_fc_tgtid_bind_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char const*) ; 
 struct Scsi_Host* transport_class_to_shost (struct device*) ; 

__attribute__((used)) static ssize_t
show_fc_private_host_tgtid_bind_type(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = transport_class_to_shost(dev);
	const char *name;

	name = get_fc_tgtid_bind_type_name(fc_host_tgtid_bind_type(shost));
	if (!name)
		return -EINVAL;
	return snprintf(buf, FC_BINDTYPE_MAX_NAMELEN, "%s\n", name);
}
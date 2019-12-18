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
typedef  int /*<<< orphan*/  __u64 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int IF_NAMESIZE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ifindex_to_name_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  p_err (char*,...) ; 
 int /*<<< orphan*/  p_info (char*) ; 
 int read_sysfs_netdev_hex_int (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

const char *
ifindex_to_bfd_params(__u32 ifindex, __u64 ns_dev, __u64 ns_ino,
		      const char **opt)
{
	char devname[IF_NAMESIZE];
	int vendor_id;
	int device_id;

	if (!ifindex_to_name_ns(ifindex, ns_dev, ns_ino, devname)) {
		p_err("Can't get net device name for ifindex %d: %s", ifindex,
		      strerror(errno));
		return NULL;
	}

	vendor_id = read_sysfs_netdev_hex_int(devname, "vendor");
	if (vendor_id < 0) {
		p_err("Can't get device vendor id for %s", devname);
		return NULL;
	}

	switch (vendor_id) {
	case 0x19ee:
		device_id = read_sysfs_netdev_hex_int(devname, "device");
		if (device_id != 0x4000 &&
		    device_id != 0x6000 &&
		    device_id != 0x6003)
			p_info("Unknown NFP device ID, assuming it is NFP-6xxx arch");
		*opt = "ctx4";
		return "NFP-6xxx";
	default:
		p_err("Can't get bfd arch name for device vendor id 0x%04x",
		      vendor_id);
		return NULL;
	}
}
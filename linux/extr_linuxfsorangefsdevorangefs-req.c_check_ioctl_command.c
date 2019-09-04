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

/* Variables and functions */
 long EINVAL ; 
 long ENOIOCTLCMD ; 
 scalar_t__ ORANGEFS_DEV_MAGIC ; 
 int /*<<< orphan*/  ORANGEFS_DEV_MAXNR ; 
 int /*<<< orphan*/  _IOC_NR (unsigned int) ; 
 scalar_t__ _IOC_TYPE (unsigned int) ; 
 int /*<<< orphan*/  gossip_err (char*,unsigned int,scalar_t__,...) ; 

__attribute__((used)) static inline long check_ioctl_command(unsigned int command)
{
	/* Check for valid ioctl codes */
	if (_IOC_TYPE(command) != ORANGEFS_DEV_MAGIC) {
		gossip_err("device ioctl magic numbers don't match! Did you rebuild pvfs2-client-core/libpvfs2? [cmd %x, magic %x != %x]\n",
			command,
			_IOC_TYPE(command),
			ORANGEFS_DEV_MAGIC);
		return -EINVAL;
	}
	/* and valid ioctl commands */
	if (_IOC_NR(command) >= ORANGEFS_DEV_MAXNR || _IOC_NR(command) <= 0) {
		gossip_err("Invalid ioctl command number [%d >= %d]\n",
			   _IOC_NR(command), ORANGEFS_DEV_MAXNR);
		return -ENOIOCTLCMD;
	}
	return 0;
}
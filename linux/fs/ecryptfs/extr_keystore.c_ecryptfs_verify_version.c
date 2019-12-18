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
typedef  int u16 ;

/* Variables and functions */
 unsigned char ECRYPTFS_VERSION_MAJOR ; 
 unsigned char ECRYPTFS_VERSION_MINOR ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*,unsigned char,unsigned char) ; 

__attribute__((used)) static int ecryptfs_verify_version(u16 version)
{
	int rc = 0;
	unsigned char major;
	unsigned char minor;

	major = ((version >> 8) & 0xFF);
	minor = (version & 0xFF);
	if (major != ECRYPTFS_VERSION_MAJOR) {
		ecryptfs_printk(KERN_ERR, "Major version number mismatch. "
				"Expected [%d]; got [%d]\n",
				ECRYPTFS_VERSION_MAJOR, major);
		rc = -EINVAL;
		goto out;
	}
	if (minor != ECRYPTFS_VERSION_MINOR) {
		ecryptfs_printk(KERN_ERR, "Minor version number mismatch. "
				"Expected [%d]; got [%d]\n",
				ECRYPTFS_VERSION_MINOR, minor);
		rc = -EINVAL;
		goto out;
	}
out:
	return rc;
}
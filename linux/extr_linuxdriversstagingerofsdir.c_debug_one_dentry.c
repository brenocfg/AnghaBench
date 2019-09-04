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

__attribute__((used)) static void debug_one_dentry(unsigned char d_type, const char *de_name,
			     unsigned int de_namelen)
{
#ifdef CONFIG_EROFS_FS_DEBUG
	/* since the on-disk name could not have the trailing '\0' */
	unsigned char dbg_namebuf[EROFS_NAME_LEN + 1];

	memcpy(dbg_namebuf, de_name, de_namelen);
	dbg_namebuf[de_namelen] = '\0';

	debugln("found dirent %s de_len %u d_type %d", dbg_namebuf,
		de_namelen, d_type);
#endif
}
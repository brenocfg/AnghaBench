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
struct squashfs_decompressor {int /*<<< orphan*/  name; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*,...) ; 
 short SQUASHFS_MAJOR ; 
 short SQUASHFS_MINOR ; 
 struct squashfs_decompressor* squashfs_lookup_decompressor (short) ; 

__attribute__((used)) static const struct squashfs_decompressor *supported_squashfs_filesystem(short
	major, short minor, short id)
{
	const struct squashfs_decompressor *decompressor;

	if (major < SQUASHFS_MAJOR) {
		ERROR("Major/Minor mismatch, older Squashfs %d.%d "
			"filesystems are unsupported\n", major, minor);
		return NULL;
	} else if (major > SQUASHFS_MAJOR || minor > SQUASHFS_MINOR) {
		ERROR("Major/Minor mismatch, trying to mount newer "
			"%d.%d filesystem\n", major, minor);
		ERROR("Please update your kernel\n");
		return NULL;
	}

	decompressor = squashfs_lookup_decompressor(id);
	if (!decompressor->supported) {
		ERROR("Filesystem uses \"%s\" compression. This is not "
			"supported\n", decompressor->name);
		return NULL;
	}

	return decompressor;
}
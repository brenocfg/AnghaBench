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
struct fs_context {int dummy; } ;

/* Variables and functions */
 short SQUASHFS_MAJOR ; 
 short SQUASHFS_MINOR ; 
 int /*<<< orphan*/  errorf (struct fs_context*,char*,...) ; 
 struct squashfs_decompressor* squashfs_lookup_decompressor (short) ; 

__attribute__((used)) static const struct squashfs_decompressor *supported_squashfs_filesystem(
	struct fs_context *fc,
	short major, short minor, short id)
{
	const struct squashfs_decompressor *decompressor;

	if (major < SQUASHFS_MAJOR) {
		errorf(fc, "Major/Minor mismatch, older Squashfs %d.%d "
		       "filesystems are unsupported", major, minor);
		return NULL;
	} else if (major > SQUASHFS_MAJOR || minor > SQUASHFS_MINOR) {
		errorf(fc, "Major/Minor mismatch, trying to mount newer "
		       "%d.%d filesystem", major, minor);
		errorf(fc, "Please update your kernel");
		return NULL;
	}

	decompressor = squashfs_lookup_decompressor(id);
	if (!decompressor->supported) {
		errorf(fc, "Filesystem uses \"%s\" compression. This is not supported",
		       decompressor->name);
		return NULL;
	}

	return decompressor;
}
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
struct super_block {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
#define  NILFS_SEG_FAIL_CHECKSUM_FULL 134 
#define  NILFS_SEG_FAIL_CHECKSUM_SUPER_ROOT 133 
#define  NILFS_SEG_FAIL_CONSISTENCY 132 
#define  NILFS_SEG_FAIL_IO 131 
#define  NILFS_SEG_FAIL_MAGIC 130 
#define  NILFS_SEG_FAIL_SEQ 129 
#define  NILFS_SEG_NO_SUPER_ROOT 128 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int nilfs_warn_segment_error(struct super_block *sb, int err)
{
	const char *msg = NULL;

	switch (err) {
	case NILFS_SEG_FAIL_IO:
		nilfs_msg(sb, KERN_ERR, "I/O error reading segment");
		return -EIO;
	case NILFS_SEG_FAIL_MAGIC:
		msg = "Magic number mismatch";
		break;
	case NILFS_SEG_FAIL_SEQ:
		msg = "Sequence number mismatch";
		break;
	case NILFS_SEG_FAIL_CHECKSUM_SUPER_ROOT:
		msg = "Checksum error in super root";
		break;
	case NILFS_SEG_FAIL_CHECKSUM_FULL:
		msg = "Checksum error in segment payload";
		break;
	case NILFS_SEG_FAIL_CONSISTENCY:
		msg = "Inconsistency found";
		break;
	case NILFS_SEG_NO_SUPER_ROOT:
		msg = "No super root in the last segment";
		break;
	default:
		nilfs_msg(sb, KERN_ERR, "unrecognized segment error %d", err);
		return -EINVAL;
	}
	nilfs_msg(sb, KERN_WARNING, "invalid segment: %s", msg);
	return -EINVAL;
}
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
struct inode {int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_ino; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  k_dir_id; } ;

/* Variables and functions */
 int FILEID_INVALID ; 
 TYPE_1__* INODE_PKEY (struct inode*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

int reiserfs_encode_fh(struct inode *inode, __u32 * data, int *lenp,
		       struct inode *parent)
{
	int maxlen = *lenp;

	if (parent && (maxlen < 5)) {
		*lenp = 5;
		return FILEID_INVALID;
	} else if (maxlen < 3) {
		*lenp = 3;
		return FILEID_INVALID;
	}

	data[0] = inode->i_ino;
	data[1] = le32_to_cpu(INODE_PKEY(inode)->k_dir_id);
	data[2] = inode->i_generation;
	*lenp = 3;
	if (parent) {
		data[3] = parent->i_ino;
		data[4] = le32_to_cpu(INODE_PKEY(parent)->k_dir_id);
		*lenp = 5;
		if (maxlen >= 6) {
			data[5] = parent->i_generation;
			*lenp = 6;
		}
	}
	return *lenp;
}
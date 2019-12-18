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
typedef  int u32 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  hash ;
struct TYPE_2__ {int uuid_hash; } ;

/* Variables and functions */
 int OCFS2_HASH_SHIFT ; 
 TYPE_1__* OCFS2_SB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ocfs2_xattr_name_hash(struct inode *inode,
				 const char *name,
				 int name_len)
{
	/* Get hash value of uuid from super block */
	u32 hash = OCFS2_SB(inode->i_sb)->uuid_hash;
	int i;

	/* hash extended attribute name */
	for (i = 0; i < name_len; i++) {
		hash = (hash << OCFS2_HASH_SHIFT) ^
		       (hash >> (8*sizeof(hash) - OCFS2_HASH_SHIFT)) ^
		       *name++;
	}

	return hash;
}
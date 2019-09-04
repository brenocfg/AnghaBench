#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nilfs_inode {int /*<<< orphan*/  i_bmap; } ;
struct TYPE_5__ {int u_flags; int /*<<< orphan*/  u_data; } ;
struct nilfs_bmap {TYPE_2__ b_u; void* b_last_allocated_ptr; int /*<<< orphan*/  b_last_allocated_key; int /*<<< orphan*/  b_ptr_type; int /*<<< orphan*/  b_sem; TYPE_1__* b_inode; scalar_t__ b_state; } ;
struct TYPE_4__ {int i_ino; } ;
struct TYPE_6__ {TYPE_1__ vfs_inode; } ;

/* Variables and functions */
 TYPE_3__* NILFS_BMAP_I (struct nilfs_bmap*) ; 
 void* NILFS_BMAP_INVALID_PTR ; 
 int NILFS_BMAP_LARGE ; 
 void* NILFS_BMAP_NEW_PTR_INIT ; 
 int /*<<< orphan*/  NILFS_BMAP_PTR_P ; 
 int /*<<< orphan*/  NILFS_BMAP_PTR_VM ; 
 int /*<<< orphan*/  NILFS_BMAP_PTR_VS ; 
 int /*<<< orphan*/  NILFS_BMAP_SIZE ; 
#define  NILFS_CPFILE_INO 131 
#define  NILFS_DAT_INO 130 
#define  NILFS_IFILE_INO 129 
#define  NILFS_SUFILE_INO 128 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_bmap_dat_lock_key ; 
 int /*<<< orphan*/  nilfs_bmap_mdt_lock_key ; 
 int nilfs_btree_init (struct nilfs_bmap*) ; 
 int nilfs_direct_init (struct nilfs_bmap*) ; 

int nilfs_bmap_read(struct nilfs_bmap *bmap, struct nilfs_inode *raw_inode)
{
	if (raw_inode == NULL)
		memset(bmap->b_u.u_data, 0, NILFS_BMAP_SIZE);
	else
		memcpy(bmap->b_u.u_data, raw_inode->i_bmap, NILFS_BMAP_SIZE);

	init_rwsem(&bmap->b_sem);
	bmap->b_state = 0;
	bmap->b_inode = &NILFS_BMAP_I(bmap)->vfs_inode;
	switch (bmap->b_inode->i_ino) {
	case NILFS_DAT_INO:
		bmap->b_ptr_type = NILFS_BMAP_PTR_P;
		bmap->b_last_allocated_key = 0;
		bmap->b_last_allocated_ptr = NILFS_BMAP_NEW_PTR_INIT;
		lockdep_set_class(&bmap->b_sem, &nilfs_bmap_dat_lock_key);
		break;
	case NILFS_CPFILE_INO:
	case NILFS_SUFILE_INO:
		bmap->b_ptr_type = NILFS_BMAP_PTR_VS;
		bmap->b_last_allocated_key = 0;
		bmap->b_last_allocated_ptr = NILFS_BMAP_INVALID_PTR;
		lockdep_set_class(&bmap->b_sem, &nilfs_bmap_mdt_lock_key);
		break;
	case NILFS_IFILE_INO:
		lockdep_set_class(&bmap->b_sem, &nilfs_bmap_mdt_lock_key);
		/* Fall through */
	default:
		bmap->b_ptr_type = NILFS_BMAP_PTR_VM;
		bmap->b_last_allocated_key = 0;
		bmap->b_last_allocated_ptr = NILFS_BMAP_INVALID_PTR;
		break;
	}

	return (bmap->b_u.u_flags & NILFS_BMAP_LARGE) ?
		nilfs_btree_init(bmap) : nilfs_direct_init(bmap);
}
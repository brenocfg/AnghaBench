#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct raparms {scalar_t__ p_ino; scalar_t__ p_dev; scalar_t__ p_count; unsigned int p_hindex; int /*<<< orphan*/  p_ra; scalar_t__ p_set; struct raparms* p_next; } ;
struct raparm_hbucket {int /*<<< orphan*/  pb_lock; struct raparms* pb_head; } ;
struct inode {scalar_t__ i_ino; TYPE_1__* i_sb; } ;
struct file {int /*<<< orphan*/  f_ra; } ;
typedef  scalar_t__ ino_t ;
typedef  scalar_t__ dev_t ;
struct TYPE_4__ {int ra_size; int /*<<< orphan*/ * ra_depth; } ;
struct TYPE_3__ {scalar_t__ s_dev; } ;

/* Variables and functions */
 unsigned int RAPARM_HASH_MASK ; 
 struct inode* file_inode (struct file*) ; 
 unsigned int jhash_2words (scalar_t__,scalar_t__,int) ; 
 TYPE_2__ nfsdstats ; 
 struct raparm_hbucket* raparm_hash ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct raparms *
nfsd_init_raparms(struct file *file)
{
	struct inode *inode = file_inode(file);
	dev_t dev = inode->i_sb->s_dev;
	ino_t ino = inode->i_ino;
	struct raparms	*ra, **rap, **frap = NULL;
	int depth = 0;
	unsigned int hash;
	struct raparm_hbucket *rab;

	hash = jhash_2words(dev, ino, 0xfeedbeef) & RAPARM_HASH_MASK;
	rab = &raparm_hash[hash];

	spin_lock(&rab->pb_lock);
	for (rap = &rab->pb_head; (ra = *rap); rap = &ra->p_next) {
		if (ra->p_ino == ino && ra->p_dev == dev)
			goto found;
		depth++;
		if (ra->p_count == 0)
			frap = rap;
	}
	depth = nfsdstats.ra_size;
	if (!frap) {	
		spin_unlock(&rab->pb_lock);
		return NULL;
	}
	rap = frap;
	ra = *frap;
	ra->p_dev = dev;
	ra->p_ino = ino;
	ra->p_set = 0;
	ra->p_hindex = hash;
found:
	if (rap != &rab->pb_head) {
		*rap = ra->p_next;
		ra->p_next   = rab->pb_head;
		rab->pb_head = ra;
	}
	ra->p_count++;
	nfsdstats.ra_depth[depth*10/nfsdstats.ra_size]++;
	spin_unlock(&rab->pb_lock);

	if (ra->p_set)
		file->f_ra = ra->p_ra;
	return ra;
}
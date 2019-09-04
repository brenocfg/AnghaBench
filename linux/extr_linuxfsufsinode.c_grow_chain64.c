#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ufs_inode_info {int /*<<< orphan*/  meta_lock; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ __fs64 ;
struct TYPE_4__ {scalar_t__ key64; scalar_t__* p; struct buffer_head* bh; } ;
typedef  TYPE_1__ Indirect ;

/* Variables and functions */
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline int grow_chain64(struct ufs_inode_info *ufsi,
			       struct buffer_head *bh, __fs64 *v,
			       Indirect *from, Indirect *to)
{
	Indirect *p;
	unsigned seq;
	to->bh = bh;
	do {
		seq = read_seqbegin(&ufsi->meta_lock);
		to->key64 = *(__fs64 *)(to->p = v);
		for (p = from; p <= to && p->key64 == *(__fs64 *)p->p; p++)
			;
	} while (read_seqretry(&ufsi->meta_lock, seq));
	return (p > to);
}
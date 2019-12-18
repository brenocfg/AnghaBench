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
struct kiocb {unsigned long ki_pos; } ;
struct iov_iter {int dummy; } ;
struct inode {int /*<<< orphan*/  i_blkbits; } ;
typedef  unsigned long loff_t ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long iov_iter_alignment (struct iov_iter*) ; 

__attribute__((used)) static inline int block_unaligned_IO(struct inode *inode,
				struct kiocb *iocb, struct iov_iter *iter)
{
	unsigned int i_blkbits = READ_ONCE(inode->i_blkbits);
	unsigned int blocksize_mask = (1 << i_blkbits) - 1;
	loff_t offset = iocb->ki_pos;
	unsigned long align = offset | iov_iter_alignment(iter);

	return align & blocksize_mask;
}
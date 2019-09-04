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
typedef  unsigned int u8 ;
struct gfs2_rbm {int offset; } ;
struct gfs2_bitmap {unsigned int* bi_clone; int /*<<< orphan*/  bi_offset; TYPE_1__* bi_bh; } ;
struct TYPE_2__ {unsigned int* b_data; } ;

/* Variables and functions */
 unsigned int const GFS2_BIT_MASK ; 
 int GFS2_BIT_SIZE ; 
 int GFS2_NBBY ; 
 struct gfs2_bitmap* rbm_bi (struct gfs2_rbm const*) ; 

__attribute__((used)) static inline u8 gfs2_testbit(const struct gfs2_rbm *rbm, bool use_clone)
{
	struct gfs2_bitmap *bi = rbm_bi(rbm);
	const u8 *buffer;
	const u8 *byte;
	unsigned int bit;

	if (use_clone && bi->bi_clone)
		buffer = bi->bi_clone;
	else
		buffer = bi->bi_bh->b_data;
	buffer += bi->bi_offset;
	byte = buffer + (rbm->offset / GFS2_NBBY);
	bit = (rbm->offset % GFS2_NBBY) * GFS2_BIT_SIZE;

	return (*byte >> bit) & GFS2_BIT_MASK;
}
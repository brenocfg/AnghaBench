#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct metapath {TYPE_1__** mp_bh; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_glock {int dummy; } ;
struct gfs2_dinode {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_5__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFS2_FORMAT_IN ; 
 int /*<<< orphan*/  GFS2_METATYPE_IN ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_buffer_clear_tail (TYPE_1__*,int) ; 
 TYPE_1__* gfs2_meta_new (struct gfs2_glock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_metatype_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (struct gfs2_glock*,TYPE_1__*) ; 

__attribute__((used)) static inline __be64 *gfs2_indirect_init(struct metapath *mp,
					 struct gfs2_glock *gl, unsigned int i,
					 unsigned offset, u64 bn)
{
	__be64 *ptr = (__be64 *)(mp->mp_bh[i - 1]->b_data +
		       ((i > 1) ? sizeof(struct gfs2_meta_header) :
				 sizeof(struct gfs2_dinode)));
	BUG_ON(i < 1);
	BUG_ON(mp->mp_bh[i] != NULL);
	mp->mp_bh[i] = gfs2_meta_new(gl, bn);
	gfs2_trans_add_meta(gl, mp->mp_bh[i]);
	gfs2_metatype_set(mp->mp_bh[i], GFS2_METATYPE_IN, GFS2_FORMAT_IN);
	gfs2_buffer_clear_tail(mp->mp_bh[i], sizeof(struct gfs2_meta_header));
	ptr += offset;
	*ptr = cpu_to_be64(bn);
	return ptr;
}
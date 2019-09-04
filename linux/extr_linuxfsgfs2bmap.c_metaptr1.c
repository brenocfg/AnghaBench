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
struct metapath {struct buffer_head** mp_bh; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_dinode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */

__attribute__((used)) static inline __be64 *metaptr1(unsigned int height, const struct metapath *mp)
{
	struct buffer_head *bh = mp->mp_bh[height];
	if (height == 0)
		return ((__be64 *)(bh->b_data + sizeof(struct gfs2_dinode)));
	return ((__be64 *)(bh->b_data + sizeof(struct gfs2_meta_header)));
}
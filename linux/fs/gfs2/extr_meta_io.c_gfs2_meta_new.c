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
typedef  int /*<<< orphan*/  u64 ;
struct gfs2_glock {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE ; 
 struct buffer_head* gfs2_getbuf (struct gfs2_glock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meta_prep_new (struct buffer_head*) ; 

struct buffer_head *gfs2_meta_new(struct gfs2_glock *gl, u64 blkno)
{
	struct buffer_head *bh;
	bh = gfs2_getbuf(gl, blkno, CREATE);
	meta_prep_new(bh);
	return bh;
}
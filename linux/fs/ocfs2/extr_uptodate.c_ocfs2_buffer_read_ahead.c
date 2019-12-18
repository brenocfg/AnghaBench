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
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ buffer_locked (struct buffer_head*) ; 
 scalar_t__ ocfs2_buffer_cached (struct ocfs2_caching_info*,struct buffer_head*) ; 

int ocfs2_buffer_read_ahead(struct ocfs2_caching_info *ci,
			    struct buffer_head *bh)
{
	return buffer_locked(bh) && ocfs2_buffer_cached(ci, bh);
}
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
typedef  int u32 ;
struct ocfs2_dinode {int dummy; } ;

/* Variables and functions */
 int ocfs2_read_links_count (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  ocfs2_set_links_count (struct ocfs2_dinode*,int) ; 

__attribute__((used)) static inline void ocfs2_add_links_count(struct ocfs2_dinode *di, int n)
{
	u32 links = ocfs2_read_links_count(di);

	links += n;

	ocfs2_set_links_count(di, links);
}
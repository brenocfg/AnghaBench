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
struct gfs2_inode {int /*<<< orphan*/  i_rw_mutex; int /*<<< orphan*/ * i_qadata; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_qadata_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void gfs2_qa_delete(struct gfs2_inode *ip, atomic_t *wcount)
{
	down_write(&ip->i_rw_mutex);
	if (ip->i_qadata && ((wcount == NULL) || (atomic_read(wcount) <= 1))) {
		kmem_cache_free(gfs2_qadata_cachep, ip->i_qadata);
		ip->i_qadata = NULL;
	}
	up_write(&ip->i_rw_mutex);
}
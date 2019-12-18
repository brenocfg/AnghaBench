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
typedef  int /*<<< orphan*/ * z_erofs_next_pcluster_t ;
struct z_erofs_unzip_io {int /*<<< orphan*/  head; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 size_t JQ_BYPASS ; 
 size_t JQ_SUBMIT ; 
 struct z_erofs_unzip_io* jobqueue_init (struct super_block*,struct z_erofs_unzip_io*,int) ; 
 int /*<<< orphan*/  tagptr1_t ; 
 void* tagptr_cast_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tagptr_fold (int /*<<< orphan*/ ,struct z_erofs_unzip_io*,int) ; 

__attribute__((used)) static void *jobqueueset_init(struct super_block *sb,
			      z_erofs_next_pcluster_t qtail[],
			      struct z_erofs_unzip_io *q[],
			      struct z_erofs_unzip_io *fgq,
			      bool forcefg)
{
	/*
	 * if managed cache is enabled, bypass jobqueue is needed,
	 * no need to read from device for all pclusters in this queue.
	 */
	q[JQ_BYPASS] = jobqueue_init(sb, fgq + JQ_BYPASS, true);
	qtail[JQ_BYPASS] = &q[JQ_BYPASS]->head;

	q[JQ_SUBMIT] = jobqueue_init(sb, fgq + JQ_SUBMIT, forcefg);
	qtail[JQ_SUBMIT] = &q[JQ_SUBMIT]->head;

	return tagptr_cast_ptr(tagptr_fold(tagptr1_t, q[JQ_SUBMIT], !forcefg));
}
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
struct the_nilfs {int dummy; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_write_logs; int /*<<< orphan*/  sc_segbufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nilfs_write_logs (int /*<<< orphan*/ *,struct the_nilfs*) ; 

__attribute__((used)) static int nilfs_segctor_write(struct nilfs_sc_info *sci,
			       struct the_nilfs *nilfs)
{
	int ret;

	ret = nilfs_write_logs(&sci->sc_segbufs, nilfs);
	list_splice_tail_init(&sci->sc_segbufs, &sci->sc_write_logs);
	return ret;
}
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
typedef  int /*<<< orphan*/  time64_t ;
struct the_nilfs {int /*<<< orphan*/  ns_segctor_sem; int /*<<< orphan*/  ns_nongc_ctime; } ;
struct nilfs_segctor_attr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_SHOW_TIME (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
nilfs_segctor_last_nongc_write_time_show(struct nilfs_segctor_attr *attr,
					 struct the_nilfs *nilfs,
					 char *buf)
{
	time64_t nongc_ctime;

	down_read(&nilfs->ns_segctor_sem);
	nongc_ctime = nilfs->ns_nongc_ctime;
	up_read(&nilfs->ns_segctor_sem);

	return NILFS_SHOW_TIME(nongc_ctime, buf);
}
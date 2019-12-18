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
struct flock64 {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_start; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;
struct flock {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_start; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;
struct file_lock {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int flock64_to_posix_lock (struct file*,struct file_lock*,struct flock64*) ; 

__attribute__((used)) static int flock_to_posix_lock(struct file *filp, struct file_lock *fl,
			       struct flock *l)
{
	struct flock64 ll = {
		.l_type = l->l_type,
		.l_whence = l->l_whence,
		.l_start = l->l_start,
		.l_len = l->l_len,
	};

	return flock64_to_posix_lock(filp, fl, &ll);
}
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
struct timespec64 {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  timespec64_equal (int /*<<< orphan*/ *,struct timespec64 const*) ; 

__attribute__((used)) static inline int mctime_update_needed(const struct inode *inode,
				       const struct timespec64 *now)
{
	if (!timespec64_equal(&inode->i_mtime, now) ||
	    !timespec64_equal(&inode->i_ctime, now))
		return 1;
	return 0;
}
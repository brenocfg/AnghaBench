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
struct iov_iter {int dummy; } ;
struct fuse_copy_state {int write; struct iov_iter* iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct fuse_copy_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fuse_copy_init(struct fuse_copy_state *cs, int write,
			   struct iov_iter *iter)
{
	memset(cs, 0, sizeof(*cs));
	cs->write = write;
	cs->iter = iter;
}
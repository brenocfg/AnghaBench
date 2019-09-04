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
struct kiocb {int /*<<< orphan*/  ki_filp; } ;
struct iov_iter {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  GOSSIP_INODE_DEBUG ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t orangefs_direct_IO(struct kiocb *iocb,
				  struct iov_iter *iter)
{
	gossip_debug(GOSSIP_INODE_DEBUG,
		     "orangefs_direct_IO: %pD\n",
		     iocb->ki_filp);

	return -EINVAL;
}
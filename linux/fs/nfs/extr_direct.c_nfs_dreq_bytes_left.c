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
struct nfs_direct_req {int /*<<< orphan*/  bytes_left; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */

ssize_t nfs_dreq_bytes_left(struct nfs_direct_req *dreq)
{
	return dreq->bytes_left;
}
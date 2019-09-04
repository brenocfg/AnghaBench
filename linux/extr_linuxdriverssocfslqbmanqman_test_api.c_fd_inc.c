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
typedef  int u64 ;
struct qm_fd {int /*<<< orphan*/  cmd; } ;
typedef  enum qm_fd_format { ____Placeholder_qm_fd_format } qm_fd_format ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int qm_fd_addr_get64 (struct qm_fd*) ; 
 int /*<<< orphan*/  qm_fd_addr_set64 (struct qm_fd*,int) ; 
 int qm_fd_get_format (struct qm_fd*) ; 
 unsigned int qm_fd_get_length (struct qm_fd*) ; 
 unsigned int qm_fd_get_offset (struct qm_fd*) ; 
 int /*<<< orphan*/  qm_fd_set_param (struct qm_fd*,int,unsigned int,unsigned int) ; 

__attribute__((used)) static void fd_inc(struct qm_fd *fd)
{
	u64 t = qm_fd_addr_get64(fd);
	int z = t >> 40;
	unsigned int len, off;
	enum qm_fd_format fmt;

	t <<= 1;
	if (z)
		t |= 1;
	qm_fd_addr_set64(fd, t);

	fmt = qm_fd_get_format(fd);
	off = qm_fd_get_offset(fd);
	len = qm_fd_get_length(fd);
	len--;
	qm_fd_set_param(fd, fmt, off, len);

	fd->cmd = cpu_to_be32(be32_to_cpu(fd->cmd) + 1);
}
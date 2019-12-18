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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint ;
struct xfs_log_vec {int dummy; } ;
struct xfs_log_iovec {int dummy; } ;

/* Variables and functions */
 int round_up (int,int) ; 

__attribute__((used)) static inline int
xlog_cil_iovec_space(
	uint	niovecs)
{
	return round_up((sizeof(struct xfs_log_vec) +
					niovecs * sizeof(struct xfs_log_iovec)),
			sizeof(uint64_t));
}
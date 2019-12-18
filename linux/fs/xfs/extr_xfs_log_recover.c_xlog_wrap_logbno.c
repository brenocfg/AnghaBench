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
typedef  int xfs_daddr_t ;
struct xlog {int /*<<< orphan*/  l_logBBsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  div_s64_rem (int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline xfs_daddr_t
xlog_wrap_logbno(
	struct xlog		*log,
	xfs_daddr_t		bno)
{
	int			mod;

	div_s64_rem(bno, log->l_logBBsize, &mod);
	return mod;
}
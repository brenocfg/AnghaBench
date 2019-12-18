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
struct xlog {int l_logsize; } ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 scalar_t__ atomic64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 scalar_t__ xlog_assign_grant_head_val (int,int) ; 
 int /*<<< orphan*/  xlog_crack_grant_head_val (scalar_t__,int*,int*) ; 

__attribute__((used)) static void
xlog_grant_add_space(
	struct xlog		*log,
	atomic64_t		*head,
	int			bytes)
{
	int64_t	head_val = atomic64_read(head);
	int64_t new, old;

	do {
		int		tmp;
		int		cycle, space;

		xlog_crack_grant_head_val(head_val, &cycle, &space);

		tmp = log->l_logsize - space;
		if (tmp > bytes)
			space += bytes;
		else {
			space = bytes - tmp;
			cycle++;
		}

		old = head_val;
		new = xlog_assign_grant_head_val(cycle, space);
		head_val = atomic64_cmpxchg(head, old, new);
	} while (head_val != old);
}
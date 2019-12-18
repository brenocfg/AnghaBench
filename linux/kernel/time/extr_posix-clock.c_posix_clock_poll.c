#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* poll ) (struct posix_clock*,struct file*,int /*<<< orphan*/ *) ;} ;
struct posix_clock {TYPE_1__ ops; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLERR ; 
 struct posix_clock* get_posix_clock (struct file*) ; 
 int /*<<< orphan*/  put_posix_clock (struct posix_clock*) ; 
 int /*<<< orphan*/  stub1 (struct posix_clock*,struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t posix_clock_poll(struct file *fp, poll_table *wait)
{
	struct posix_clock *clk = get_posix_clock(fp);
	__poll_t result = 0;

	if (!clk)
		return EPOLLERR;

	if (clk->ops.poll)
		result = clk->ops.poll(clk, fp, wait);

	put_posix_clock(clk);

	return result;
}
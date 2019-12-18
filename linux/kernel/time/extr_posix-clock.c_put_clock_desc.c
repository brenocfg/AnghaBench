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
struct posix_clock_desc {int /*<<< orphan*/  fp; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_posix_clock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_clock_desc(struct posix_clock_desc *cd)
{
	put_posix_clock(cd->clk);
	fput(cd->fp);
}
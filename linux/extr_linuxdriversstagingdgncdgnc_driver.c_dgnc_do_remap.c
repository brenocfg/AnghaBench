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
struct dgnc_board {int /*<<< orphan*/  re_map_membase; int /*<<< orphan*/  membase; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dgnc_do_remap(struct dgnc_board *brd)
{
	brd->re_map_membase = ioremap(brd->membase, 0x1000);
	if (!brd->re_map_membase)
		return -ENOMEM;

	return 0;
}
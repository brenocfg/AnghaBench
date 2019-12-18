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
struct ubifs_zbranch {int lnum; int offs; } ;

/* Variables and functions */

__attribute__((used)) static int matches_position(struct ubifs_zbranch *zbr, int lnum, int offs)
{
	if (zbr->lnum == lnum && zbr->offs == offs)
		return 1;
	else
		return 0;
}
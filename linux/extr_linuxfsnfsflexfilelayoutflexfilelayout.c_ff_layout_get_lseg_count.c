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
struct nfs4_ff_layout_segment {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
ff_layout_get_lseg_count(struct nfs4_ff_layout_segment *fls)
{
	return 1;
}
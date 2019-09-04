#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs4_ff_layout_segment {int mirror_array_cnt; TYPE_1__** mirror_array; } ;
struct TYPE_3__ {scalar_t__ efficiency; } ;

/* Variables and functions */
 int /*<<< orphan*/  swap (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void ff_layout_sort_mirrors(struct nfs4_ff_layout_segment *fls)
{
	int i, j;

	for (i = 0; i < fls->mirror_array_cnt - 1; i++) {
		for (j = i + 1; j < fls->mirror_array_cnt; j++)
			if (fls->mirror_array[i]->efficiency <
			    fls->mirror_array[j]->efficiency)
				swap(fls->mirror_array[i],
				     fls->mirror_array[j]);
	}
}
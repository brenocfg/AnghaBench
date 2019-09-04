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
struct remap_data {size_t h_iter; unsigned long* h_gpfns; int /*<<< orphan*/ * fgfn; scalar_t__* h_errs; int /*<<< orphan*/ * h_idxs; } ;

/* Variables and functions */

__attribute__((used)) static void setup_hparams(unsigned long gfn, void *data)
{
	struct remap_data *info = data;

	info->h_idxs[info->h_iter] = *info->fgfn;
	info->h_gpfns[info->h_iter] = gfn;
	info->h_errs[info->h_iter] = 0;

	info->h_iter++;
	info->fgfn++;
}
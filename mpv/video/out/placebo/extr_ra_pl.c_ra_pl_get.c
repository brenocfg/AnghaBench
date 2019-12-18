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
struct ra {int /*<<< orphan*/ * fns; } ;
struct pl_gpu {int dummy; } ;

/* Variables and functions */
 struct pl_gpu const* get_gpu (struct ra const*) ; 
 int /*<<< orphan*/  ra_fns_pl ; 

const struct pl_gpu *ra_pl_get(const struct ra *ra)
{
    return ra->fns == &ra_fns_pl ? get_gpu(ra) : NULL;
}
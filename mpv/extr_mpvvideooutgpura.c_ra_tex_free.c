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
struct ra_tex {int dummy; } ;
struct ra {TYPE_1__* fns; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tex_destroy ) (struct ra*,struct ra_tex*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ra*,struct ra_tex*) ; 

void ra_tex_free(struct ra *ra, struct ra_tex **tex)
{
    if (*tex)
        ra->fns->tex_destroy(ra, *tex);
    *tex = NULL;
}
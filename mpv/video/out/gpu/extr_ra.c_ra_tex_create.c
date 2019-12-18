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
struct ra_tex_params {int dummy; } ;
struct ra_tex {int dummy; } ;
struct ra {TYPE_1__* fns; } ;
struct TYPE_2__ {struct ra_tex* (* tex_create ) (struct ra*,struct ra_tex_params const*) ;} ;

/* Variables and functions */
 struct ra_tex* stub1 (struct ra*,struct ra_tex_params const*) ; 

struct ra_tex *ra_tex_create(struct ra *ra, const struct ra_tex_params *params)
{
    return ra->fns->tex_create(ra, params);
}
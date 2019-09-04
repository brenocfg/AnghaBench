#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct image {TYPE_3__* tex; } ;
struct TYPE_5__ {TYPE_1__* format; } ;
struct TYPE_6__ {TYPE_2__ params; } ;
struct TYPE_4__ {scalar_t__ luminance_alpha; } ;

/* Variables and functions */

__attribute__((used)) static const char *get_tex_swizzle(struct image *img)
{
    if (!img->tex)
        return "rgba";
    return img->tex->params.format->luminance_alpha ? "raaa" : "rgba";
}
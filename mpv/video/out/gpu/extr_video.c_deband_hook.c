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
struct image {size_t type; } ;
struct TYPE_5__ {int /*<<< orphan*/  gamma; } ;
struct TYPE_6__ {TYPE_2__ color; } ;
struct TYPE_4__ {int /*<<< orphan*/  deband_opts; } ;
struct gl_video {TYPE_3__ image_params; int /*<<< orphan*/  lfg; TYPE_1__ opts; int /*<<< orphan*/  sc; } ;
struct gl_transform {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pass_describe (struct gl_video*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pass_sample_deband (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * plane_names ; 

__attribute__((used)) static void deband_hook(struct gl_video *p, struct image img,
                        struct gl_transform *trans, void *priv)
{
    pass_describe(p, "debanding (%s)", plane_names[img.type]);
    pass_sample_deband(p->sc, p->opts.deband_opts, &p->lfg,
                       p->image_params.color.gamma);
}
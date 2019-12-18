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
struct ra_tex {struct d3d_tex* priv; } ;
struct ra {int dummy; } ;
struct d3d_tex {int /*<<< orphan*/  staging; int /*<<< orphan*/  res; int /*<<< orphan*/  sampler; int /*<<< orphan*/  uav; int /*<<< orphan*/  rtv; int /*<<< orphan*/  srv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct ra_tex*) ; 

__attribute__((used)) static void tex_destroy(struct ra *ra, struct ra_tex *tex)
{
    if (!tex)
        return;
    struct d3d_tex *tex_p = tex->priv;

    SAFE_RELEASE(tex_p->srv);
    SAFE_RELEASE(tex_p->rtv);
    SAFE_RELEASE(tex_p->uav);
    SAFE_RELEASE(tex_p->sampler);
    SAFE_RELEASE(tex_p->res);
    SAFE_RELEASE(tex_p->staging);
    talloc_free(tex);
}
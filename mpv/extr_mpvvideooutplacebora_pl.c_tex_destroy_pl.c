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
struct ra_tex {int /*<<< orphan*/  priv; } ;
struct ra {int dummy; } ;
struct pl_tex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_gpu (struct ra*) ; 
 int /*<<< orphan*/  pl_tex_destroy (int /*<<< orphan*/ ,struct pl_tex const**) ; 
 int /*<<< orphan*/  talloc_free (struct ra_tex*) ; 

__attribute__((used)) static void tex_destroy_pl(struct ra *ra, struct ra_tex *tex)
{
    if (!tex)
        return;

    pl_tex_destroy(get_gpu(ra), (const struct pl_tex **) &tex->priv);
    talloc_free(tex);
}
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
struct ra_renderpass {struct pass_priv* priv; } ;
struct ra {int dummy; } ;
struct pl_pass {int dummy; } ;
struct pass_priv {int /*<<< orphan*/  pl_pass; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_gpu (struct ra*) ; 
 int /*<<< orphan*/  pl_pass_destroy (int /*<<< orphan*/ ,struct pl_pass const**) ; 
 int /*<<< orphan*/  talloc_free (struct ra_renderpass*) ; 

__attribute__((used)) static void renderpass_destroy_pl(struct ra *ra, struct ra_renderpass *pass)
{
    if (!pass)
        return;

    struct pass_priv *priv = pass->priv;
    pl_pass_destroy(get_gpu(ra), (const struct pl_pass **) &priv->pl_pass);
    talloc_free(pass);
}
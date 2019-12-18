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
struct sd_lavc_priv {int /*<<< orphan*/  avctx; int /*<<< orphan*/ * subs; } ;
struct sd {struct sd_lavc_priv* priv; } ;

/* Variables and functions */
 int MAX_QUEUE ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_sub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct sd_lavc_priv*) ; 

__attribute__((used)) static void uninit(struct sd *sd)
{
    struct sd_lavc_priv *priv = sd->priv;

    for (int n = 0; n < MAX_QUEUE; n++)
        clear_sub(&priv->subs[n]);
    avcodec_free_context(&priv->avctx);
    talloc_free(priv);
}
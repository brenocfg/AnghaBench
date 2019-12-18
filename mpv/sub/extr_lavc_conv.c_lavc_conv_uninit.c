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
struct lavc_conv {int /*<<< orphan*/  avctx; int /*<<< orphan*/  cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avsubtitle_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct lavc_conv*) ; 

void lavc_conv_uninit(struct lavc_conv *priv)
{
    avsubtitle_free(&priv->cur);
    avcodec_free_context(&priv->avctx);
    talloc_free(priv);
}
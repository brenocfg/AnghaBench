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
struct vo {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  canvas; int /*<<< orphan*/  display; int /*<<< orphan*/ * dither_buffer; int /*<<< orphan*/ * dither; } ;

/* Variables and functions */
 int /*<<< orphan*/  caca_free_canvas (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_free_display (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_free_dither (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    struct priv *priv = vo->priv;
    caca_free_dither(priv->dither);
    priv->dither = NULL;
    talloc_free(priv->dither_buffer);
    priv->dither_buffer = NULL;
    caca_free_display(priv->display);
    caca_free_canvas(priv->canvas);
}
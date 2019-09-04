#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vo {struct priv* priv; } ;
struct priv {int image_width; int /*<<< orphan*/  dither_buffer; int /*<<< orphan*/  dither; int /*<<< orphan*/  screen_h; int /*<<< orphan*/  screen_w; int /*<<< orphan*/  canvas; int /*<<< orphan*/  image_height; } ;
struct TYPE_4__ {int /*<<< orphan*/ * stride; int /*<<< orphan*/ * planes; } ;
typedef  TYPE_1__ mp_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  caca_dither_bitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int depth ; 
 int /*<<< orphan*/  memcpy_pic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (TYPE_1__*) ; 

__attribute__((used)) static void draw_image(struct vo *vo, mp_image_t *mpi)
{
    struct priv *priv = vo->priv;
    memcpy_pic(priv->dither_buffer, mpi->planes[0], priv->image_width * depth, priv->image_height,
               priv->image_width * depth, mpi->stride[0]);
    caca_dither_bitmap(priv->canvas, 0, 0, priv->screen_w, priv->screen_h, priv->dither, priv->dither_buffer);
    talloc_free(mpi);
}
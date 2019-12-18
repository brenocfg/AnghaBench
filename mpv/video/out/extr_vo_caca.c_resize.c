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
struct priv {int image_width; int image_height; int /*<<< orphan*/  dither_algo; int /*<<< orphan*/ * dither; int /*<<< orphan*/  dither_color; int /*<<< orphan*/  dither_charset; int /*<<< orphan*/  dither_antialias; int /*<<< orphan*/  dither_buffer; int /*<<< orphan*/  canvas; int /*<<< orphan*/  screen_h; int /*<<< orphan*/  screen_w; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int /*<<< orphan*/  amask ; 
 int /*<<< orphan*/  bmask ; 
 int /*<<< orphan*/  bpp ; 
 int /*<<< orphan*/ * caca_create_dither (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_free_dither (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  caca_get_canvas_height (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_get_canvas_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_set_dither_algorithm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_set_dither_antialias (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_set_dither_charset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_set_dither_color (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int depth ; 
 int /*<<< orphan*/  gmask ; 
 int /*<<< orphan*/  rmask ; 
 int /*<<< orphan*/  talloc_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint8_t ; 

__attribute__((used)) static int resize(struct vo *vo)
{
    struct priv *priv = vo->priv;
    priv->screen_w = caca_get_canvas_width(priv->canvas);
    priv->screen_h = caca_get_canvas_height(priv->canvas);

    caca_free_dither(priv->dither);
    talloc_free(priv->dither_buffer);

    priv->dither = caca_create_dither(bpp, priv->image_width, priv->image_height,
                                depth * priv->image_width,
                                rmask, gmask, bmask, amask);
    if (priv->dither == NULL) {
        MP_FATAL(vo, "caca_create_dither failed!\n");
        return -1;
    }
    priv->dither_buffer =
        talloc_array(NULL, uint8_t, depth * priv->image_width * priv->image_height);

    /* Default libcaca features */
    caca_set_dither_antialias(priv->dither, priv->dither_antialias);
    caca_set_dither_charset(priv->dither, priv->dither_charset);
    caca_set_dither_color(priv->dither, priv->dither_color);
    caca_set_dither_algorithm(priv->dither, priv->dither_algo);

    return 0;
}
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
struct priv {char* dither_antialias; char* dither_charset; char* dither_color; char* dither_algo; int /*<<< orphan*/ * canvas; int /*<<< orphan*/ * display; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  MP_ERR (struct vo*,char*) ; 
 int /*<<< orphan*/ * caca_create_canvas (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * caca_create_display (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  caca_free_canvas (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int preinit(struct vo *vo)
{
    struct priv *priv = vo->priv;

    priv->dither_antialias = "default";
    priv->dither_charset   = "default";
    priv->dither_color     = "default";
    priv->dither_algo      = "none";

    priv->canvas = caca_create_canvas(0, 0);
    if (priv->canvas == NULL) {
        MP_ERR(vo, "failed to create canvas\n");
        return ENOSYS;
    }

    priv->display = caca_create_display(priv->canvas);

    if (priv->display == NULL) {
        MP_ERR(vo, "failed to create display\n");
        caca_free_canvas(priv->canvas);
        return ENOSYS;
    }

    return 0;
}
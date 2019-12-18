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
struct priv {int /*<<< orphan*/  image_format; int /*<<< orphan*/  image_width; int /*<<< orphan*/  image_height; } ;
struct mp_image_params {int /*<<< orphan*/  imgfmt; int /*<<< orphan*/  w; int /*<<< orphan*/  h; } ;

/* Variables and functions */
 int resize (struct vo*) ; 

__attribute__((used)) static int reconfig(struct vo *vo, struct mp_image_params *params)
{
    struct priv *priv = vo->priv;
    priv->image_height = params->h;
    priv->image_width  = params->w;
    priv->image_format = params->imgfmt;

    return resize(vo);
}
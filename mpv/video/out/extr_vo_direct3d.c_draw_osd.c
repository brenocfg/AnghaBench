#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vo {int /*<<< orphan*/  osd; TYPE_1__* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  osd_pts; int /*<<< orphan*/  osd_res; int /*<<< orphan*/ * osd_fmt_table; int /*<<< orphan*/  d3d_device; } ;
typedef  TYPE_1__ d3d_priv ;

/* Variables and functions */
 int SUBBITMAP_COUNT ; 
 int /*<<< orphan*/  draw_osd_cb ; 
 int /*<<< orphan*/  osd_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void draw_osd(struct vo *vo)
{
    d3d_priv *priv = vo->priv;
    if (!priv->d3d_device)
        return;

    bool osd_fmt_supported[SUBBITMAP_COUNT];
    for (int n = 0; n < SUBBITMAP_COUNT; n++)
        osd_fmt_supported[n] = !!priv->osd_fmt_table[n];

    osd_draw(vo->osd, priv->osd_res, priv->osd_pts, 0, osd_fmt_supported,
             draw_osd_cb, priv);
}
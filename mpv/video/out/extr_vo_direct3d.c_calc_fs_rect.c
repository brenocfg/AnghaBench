#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mp_rect {int /*<<< orphan*/  y1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x1; int /*<<< orphan*/  x0; } ;
struct TYPE_6__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct TYPE_5__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct TYPE_7__ {TYPE_2__ fs_panscan_rect; TYPE_1__ fs_movie_rect; int /*<<< orphan*/  osd_res; int /*<<< orphan*/  vo; } ;
typedef  TYPE_3__ d3d_priv ;

/* Variables and functions */
 int /*<<< orphan*/  vo_get_src_dst_rects (int /*<<< orphan*/ ,struct mp_rect*,struct mp_rect*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void calc_fs_rect(d3d_priv *priv)
{
    struct mp_rect src_rect;
    struct mp_rect dst_rect;
    vo_get_src_dst_rects(priv->vo, &src_rect, &dst_rect, &priv->osd_res);

    priv->fs_movie_rect.left     = dst_rect.x0;
    priv->fs_movie_rect.right    = dst_rect.x1;
    priv->fs_movie_rect.top      = dst_rect.y0;
    priv->fs_movie_rect.bottom   = dst_rect.y1;
    priv->fs_panscan_rect.left   = src_rect.x0;
    priv->fs_panscan_rect.right  = src_rect.x1;
    priv->fs_panscan_rect.top    = src_rect.y0;
    priv->fs_panscan_rect.bottom = src_rect.y1;
}
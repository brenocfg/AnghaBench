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
struct sub_bitmaps {scalar_t__ num_parts; size_t format; size_t render_index; scalar_t__ change_id; } ;
struct osdpart {scalar_t__ change_id; scalar_t__ num_vertices; } ;
struct TYPE_4__ {struct osdpart** osd; int /*<<< orphan*/ * osd_fmt_table; } ;
typedef  TYPE_1__ d3d_priv ;

/* Variables and functions */
 int /*<<< orphan*/  upload_osd (TYPE_1__*,struct osdpart*,struct sub_bitmaps*) ; 

__attribute__((used)) static struct osdpart *generate_osd(d3d_priv *priv, struct sub_bitmaps *imgs)
{
    if (imgs->num_parts == 0 || !priv->osd_fmt_table[imgs->format])
        return NULL;

    struct osdpart *osd = priv->osd[imgs->render_index];

    if (imgs->change_id != osd->change_id)
        upload_osd(priv, osd, imgs);

    return osd->num_vertices ? osd : NULL;
}
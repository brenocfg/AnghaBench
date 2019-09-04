#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct priv {TYPE_2__* vsapi; } ;
struct TYPE_3__ {scalar_t__ levels; int /*<<< orphan*/  space; } ;
struct mp_image_params {int p_w; int p_h; scalar_t__ chroma_location; TYPE_1__ color; } ;
struct mp_image {int pict_type; int fields; struct mp_image_params params; } ;
typedef  int /*<<< orphan*/  VSMap ;
struct TYPE_4__ {int /*<<< orphan*/  (* propSetInt ) (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* propSetData ) (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ MP_CHROMA_CENTER ; 
 scalar_t__ MP_CSP_LEVELS_TV ; 
 int MP_IMGFIELD_INTERLACED ; 
 int MP_IMGFIELD_TOP_FIRST ; 
 int mp_csp_to_avcol_spc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_mp_to_vs_frame_props_map(struct priv *p, VSMap *map,
                                          struct mp_image *img)
{
    struct mp_image_params *params = &img->params;
    p->vsapi->propSetInt(map, "_SARNum", params->p_w, 0);
    p->vsapi->propSetInt(map, "_SARDen", params->p_h, 0);
    if (params->color.levels) {
        p->vsapi->propSetInt(map, "_ColorRange",
                params->color.levels == MP_CSP_LEVELS_TV, 0);
    }
    // The docs explicitly say it uses libavcodec values.
    p->vsapi->propSetInt(map, "_ColorSpace",
            mp_csp_to_avcol_spc(params->color.space), 0);
    if (params->chroma_location) {
        p->vsapi->propSetInt(map, "_ChromaLocation",
                params->chroma_location == MP_CHROMA_CENTER, 0);
    }
    char pict_type = 0;
    switch (img->pict_type) {
    case 1: pict_type = 'I'; break;
    case 2: pict_type = 'P'; break;
    case 3: pict_type = 'B'; break;
    }
    if (pict_type)
        p->vsapi->propSetData(map, "_PictType", &pict_type, 1, 0);
    int field = 0;
    if (img->fields & MP_IMGFIELD_INTERLACED)
        field = img->fields & MP_IMGFIELD_TOP_FIRST ? 2 : 1;
    p->vsapi->propSetInt(map, "_FieldBased", field, 0);
}
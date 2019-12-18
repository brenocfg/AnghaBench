#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct priv {TYPE_1__* vsapi; } ;
struct mp_image {int dummy; } ;
typedef  int /*<<< orphan*/  VSMap ;
typedef  int /*<<< orphan*/  VSFrameRef ;
struct TYPE_2__ {int /*<<< orphan*/  (* propSetInt ) (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* getFramePropsRW ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  copy_mp_to_vs_frame_props_map (struct priv*,int /*<<< orphan*/ *,struct mp_image*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_vs_frame_props(struct priv *p, VSFrameRef *frame,
                              struct mp_image *img, int dur_num, int dur_den)
{
    VSMap *map = p->vsapi->getFramePropsRW(frame);
    if (!map)
        return -1;
    p->vsapi->propSetInt(map, "_DurationNum", dur_num, 0);
    p->vsapi->propSetInt(map, "_DurationDen", dur_den, 0);
    copy_mp_to_vs_frame_props_map(p, map, img);
    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vo {TYPE_1__* driver; int /*<<< orphan*/ * osd; int /*<<< orphan*/ * hwdec_devs; } ;
struct mp_output_chain {TYPE_2__* f; } ;
struct TYPE_6__ {int rotate90; struct vo* dr_vo; int /*<<< orphan*/ * osd; int /*<<< orphan*/ * hwdec_devs; } ;
struct chain {struct vo* vo; TYPE_3__ stream_info; } ;
struct TYPE_5__ {struct chain* priv; } ;
struct TYPE_4__ {int caps; } ;

/* Variables and functions */
 int VO_CAP_ROTATE90 ; 
 int /*<<< orphan*/  update_output_caps (struct chain*) ; 

void mp_output_chain_set_vo(struct mp_output_chain *c, struct vo *vo)
{
    struct chain *p = c->f->priv;

    p->stream_info.hwdec_devs = vo ? vo->hwdec_devs : NULL;
    p->stream_info.osd = vo ? vo->osd : NULL;
    p->stream_info.rotate90 = vo ? vo->driver->caps & VO_CAP_ROTATE90 : false;
    p->stream_info.dr_vo = vo;
    p->vo = vo;
    update_output_caps(p);
}
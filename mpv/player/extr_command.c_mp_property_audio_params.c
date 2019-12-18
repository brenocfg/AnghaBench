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
struct m_property {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ao_chain; } ;
struct TYPE_5__ {TYPE_1__* filter; } ;
struct TYPE_4__ {int /*<<< orphan*/ * input_aformat; } ;
typedef  TYPE_3__ MPContext ;

/* Variables and functions */
 int property_audiofmt (int /*<<< orphan*/ *,int,void*) ; 

__attribute__((used)) static int mp_property_audio_params(void *ctx, struct m_property *prop,
                                    int action, void *arg)
{
    MPContext *mpctx = ctx;
    return property_audiofmt(mpctx->ao_chain ?
        mpctx->ao_chain->filter->input_aformat : NULL, action, arg);
}
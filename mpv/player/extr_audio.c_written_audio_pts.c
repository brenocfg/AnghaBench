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
struct ao_chain {double last_out_pts; int /*<<< orphan*/  ao_buffer; } ;
struct MPContext {double audio_speed; struct ao_chain* ao_chain; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 double mp_audio_buffer_seconds (int /*<<< orphan*/ ) ; 

double written_audio_pts(struct MPContext *mpctx)
{
    struct ao_chain *ao_c = mpctx->ao_chain;
    if (!ao_c)
        return MP_NOPTS_VALUE;

    // end pts of audio that has been output by filters
    double a_pts = ao_c->last_out_pts;
    if (a_pts == MP_NOPTS_VALUE)
        return MP_NOPTS_VALUE;

    // Data that was ready for ao but was buffered because ao didn't fully
    // accept everything to internal buffers yet. This also does not correctly
    // track playback speed, so we use the current speed.
    a_pts -= mp_audio_buffer_seconds(ao_c->ao_buffer) * mpctx->audio_speed;

    return a_pts;
}
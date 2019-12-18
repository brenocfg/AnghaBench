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
struct MPContext {double audio_speed; int /*<<< orphan*/  ao; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 double ao_get_delay (int /*<<< orphan*/ ) ; 
 double written_audio_pts (struct MPContext*) ; 

double playing_audio_pts(struct MPContext *mpctx)
{
    double pts = written_audio_pts(mpctx);
    if (pts == MP_NOPTS_VALUE || !mpctx->ao)
        return pts;
    return pts - mpctx->audio_speed * ao_get_delay(mpctx->ao);
}
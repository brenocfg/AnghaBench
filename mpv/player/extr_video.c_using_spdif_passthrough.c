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
struct mp_chmap {int dummy; } ;
struct MPContext {TYPE_1__* ao_chain; } ;
struct TYPE_2__ {scalar_t__ ao; } ;

/* Variables and functions */
 int /*<<< orphan*/  af_fmt_is_pcm (int) ; 
 int /*<<< orphan*/  ao_get_format (scalar_t__,int*,int*,struct mp_chmap*) ; 

__attribute__((used)) static bool using_spdif_passthrough(struct MPContext *mpctx)
{
    if (mpctx->ao_chain && mpctx->ao_chain->ao) {
        int samplerate;
        int format;
        struct mp_chmap channels;
        ao_get_format(mpctx->ao_chain->ao, &samplerate, &format, &channels);
        return !af_fmt_is_pcm(format);
    }
    return false;
}
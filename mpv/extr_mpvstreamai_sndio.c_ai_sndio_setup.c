#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sio_par {int bits; int sig; int bps; int round; int /*<<< orphan*/  rate; int /*<<< orphan*/  rchan; int /*<<< orphan*/  appbufsz; int /*<<< orphan*/  le; } ;
struct TYPE_5__ {int /*<<< orphan*/  hdl; } ;
struct TYPE_6__ {int samplesize; int bytes_per_sample; int blocksize; int /*<<< orphan*/  samplerate; int /*<<< orphan*/  channels; TYPE_1__ sndio; int /*<<< orphan*/  req_samplerate; int /*<<< orphan*/  req_channels; } ;
typedef  TYPE_2__ audio_in_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  SIO_LE_NATIVE ; 
 int /*<<< orphan*/  sio_getpar (int /*<<< orphan*/ ,struct sio_par*) ; 
 int /*<<< orphan*/  sio_initpar (struct sio_par*) ; 
 int /*<<< orphan*/  sio_setpar (int /*<<< orphan*/ ,struct sio_par*) ; 

int ai_sndio_setup(audio_in_t *ai)
{
    struct sio_par par;

    sio_initpar(&par);

    par.bits = 16;
    par.sig = 1;
    par.le = SIO_LE_NATIVE;
    par.rchan = ai->req_channels;
    par.rate = ai->req_samplerate;
    par.appbufsz = ai->req_samplerate;  /* 1 sec */

   if (!sio_setpar(ai->sndio.hdl, &par) || !sio_getpar(ai->sndio.hdl, &par)) {
        MP_ERR(ai, "could not configure sndio audio");
        return -1;
    }

    ai->channels = par.rchan;
    ai->samplerate = par.rate;
    ai->samplesize = par.bits;
    ai->bytes_per_sample = par.bps;
    ai->blocksize = par.round * par.bps;

    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_runtime {int rate; } ;
struct ak4114 {unsigned char rcs0; int rcs1; TYPE_1__* capture_substream; int /*<<< orphan*/  (* change_callback ) (struct ak4114*,unsigned char,unsigned char) ;int /*<<< orphan*/  lock; int /*<<< orphan*/ * errors; } ;
struct TYPE_5__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 unsigned char AK4114_AUDION ; 
 unsigned char AK4114_AUTO ; 
 unsigned char AK4114_CCRC ; 
 size_t AK4114_CCRC_ERRORS ; 
 unsigned int AK4114_CHECK_NO_RATE ; 
 unsigned int AK4114_CHECK_NO_STAT ; 
 unsigned char AK4114_CINT ; 
 unsigned char AK4114_PAR ; 
 size_t AK4114_PARITY_ERRORS ; 
 unsigned char AK4114_PEM ; 
 unsigned char AK4114_QCRC ; 
 size_t AK4114_QCRC_ERRORS ; 
 unsigned char AK4114_QINT ; 
 int /*<<< orphan*/  AK4114_REG_RCS0 ; 
 int /*<<< orphan*/  AK4114_REG_RCS1 ; 
 unsigned char AK4114_UNLCK ; 
 unsigned char AK4114_V ; 
 size_t AK4114_V_BIT_ERRORS ; 
 int /*<<< orphan*/  SNDRV_PCM_STATE_DRAINING ; 
 int /*<<< orphan*/  ak4114_notify (struct ak4114*,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int external_rate (unsigned char) ; 
 unsigned char reg_read (struct ak4114*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_running (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_pcm_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irqsave (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irqrestore (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ak4114*,unsigned char,unsigned char) ; 

int snd_ak4114_check_rate_and_errors(struct ak4114 *ak4114, unsigned int flags)
{
	struct snd_pcm_runtime *runtime = ak4114->capture_substream ? ak4114->capture_substream->runtime : NULL;
	unsigned long _flags;
	int res = 0;
	unsigned char rcs0, rcs1;
	unsigned char c0, c1;

	rcs1 = reg_read(ak4114, AK4114_REG_RCS1);
	if (flags & AK4114_CHECK_NO_STAT)
		goto __rate;
	rcs0 = reg_read(ak4114, AK4114_REG_RCS0);
	spin_lock_irqsave(&ak4114->lock, _flags);
	if (rcs0 & AK4114_PAR)
		ak4114->errors[AK4114_PARITY_ERRORS]++;
	if (rcs1 & AK4114_V)
		ak4114->errors[AK4114_V_BIT_ERRORS]++;
	if (rcs1 & AK4114_CCRC)
		ak4114->errors[AK4114_CCRC_ERRORS]++;
	if (rcs1 & AK4114_QCRC)
		ak4114->errors[AK4114_QCRC_ERRORS]++;
	c0 = (ak4114->rcs0 & (AK4114_QINT | AK4114_CINT | AK4114_PEM | AK4114_AUDION | AK4114_AUTO | AK4114_UNLCK)) ^
                     (rcs0 & (AK4114_QINT | AK4114_CINT | AK4114_PEM | AK4114_AUDION | AK4114_AUTO | AK4114_UNLCK));
	c1 = (ak4114->rcs1 & 0xf0) ^ (rcs1 & 0xf0);
	ak4114->rcs0 = rcs0 & ~(AK4114_QINT | AK4114_CINT);
	ak4114->rcs1 = rcs1;
	spin_unlock_irqrestore(&ak4114->lock, _flags);

	ak4114_notify(ak4114, rcs0, rcs1, c0, c1);
	if (ak4114->change_callback && (c0 | c1) != 0)
		ak4114->change_callback(ak4114, c0, c1);

      __rate:
	/* compare rate */
	res = external_rate(rcs1);
	if (!(flags & AK4114_CHECK_NO_RATE) && runtime && runtime->rate != res) {
		snd_pcm_stream_lock_irqsave(ak4114->capture_substream, _flags);
		if (snd_pcm_running(ak4114->capture_substream)) {
			// printk(KERN_DEBUG "rate changed (%i <- %i)\n", runtime->rate, res);
			snd_pcm_stop(ak4114->capture_substream, SNDRV_PCM_STATE_DRAINING);
			res = 1;
		}
		snd_pcm_stream_unlock_irqrestore(ak4114->capture_substream, _flags);
	}
	return res;
}
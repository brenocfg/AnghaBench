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
struct snd_pcm_substream {int dummy; } ;
struct snd_intelhad {int period_bytes; int num_bds; int pcmbuf_head; int /*<<< orphan*/  had_spinlock; int /*<<< orphan*/  dev; int /*<<< orphan*/  bd_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_BUF_LEN (int /*<<< orphan*/ ) ; 
 int EPIPE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  had_advance_ringbuf (struct snd_pcm_substream*,struct snd_intelhad*) ; 
 int /*<<< orphan*/  had_read_register (struct snd_intelhad*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int had_process_ringbuf(struct snd_pcm_substream *substream,
			       struct snd_intelhad *intelhaddata)
{
	int len, processed;
	unsigned long flags;

	processed = 0;
	spin_lock_irqsave(&intelhaddata->had_spinlock, flags);
	for (;;) {
		/* get the remaining bytes on the buffer */
		had_read_register(intelhaddata,
				  AUD_BUF_LEN(intelhaddata->bd_head),
				  &len);
		if (len < 0 || len > intelhaddata->period_bytes) {
			dev_dbg(intelhaddata->dev, "Invalid buf length %d\n",
				len);
			len = -EPIPE;
			goto out;
		}

		if (len > 0) /* OK, this is the current buffer */
			break;

		/* len=0 => already empty, check the next buffer */
		if (++processed >= intelhaddata->num_bds) {
			len = -EPIPE; /* all empty? - report underrun */
			goto out;
		}
		had_advance_ringbuf(substream, intelhaddata);
	}

	len = intelhaddata->period_bytes - len;
	len += intelhaddata->period_bytes * intelhaddata->pcmbuf_head;
 out:
	spin_unlock_irqrestore(&intelhaddata->had_spinlock, flags);
	return len;
}
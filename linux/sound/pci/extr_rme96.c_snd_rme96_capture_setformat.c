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
struct rme96 {scalar_t__ iobase; int /*<<< orphan*/  wcreg; } ;
typedef  int snd_pcm_format_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RME96_IO_CONTROL_REGISTER ; 
 int /*<<< orphan*/  RME96_WCR_MODE24_2 ; 
#define  SNDRV_PCM_FORMAT_S16_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
snd_rme96_capture_setformat(struct rme96 *rme96, snd_pcm_format_t format)
{
	switch (format) {
	case SNDRV_PCM_FORMAT_S16_LE:
		rme96->wcreg &= ~RME96_WCR_MODE24_2;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		rme96->wcreg |= RME96_WCR_MODE24_2;
		break;
	default:
		return -EINVAL;
	}
	writel(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	return 0;
}
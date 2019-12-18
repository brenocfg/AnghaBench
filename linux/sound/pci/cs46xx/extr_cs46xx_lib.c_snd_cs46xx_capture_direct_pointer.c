#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int dummy; } ;
struct TYPE_3__ {size_t addr; } ;
struct TYPE_4__ {size_t shift; TYPE_1__ hw_buf; } ;
struct snd_cs46xx {TYPE_2__ capt; } ;
typedef  size_t snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  BA1_CBA ; 
 size_t snd_cs46xx_peek (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 struct snd_cs46xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_cs46xx_capture_direct_pointer(struct snd_pcm_substream *substream)
{
	struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	size_t ptr = snd_cs46xx_peek(chip, BA1_CBA) - chip->capt.hw_buf.addr;
	return ptr >> chip->capt.shift;
}
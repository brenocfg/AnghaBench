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
struct azx_dev {int dummy; } ;
struct azx {int dummy; } ;

/* Variables and functions */
 struct azx_dev* get_azx_dev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  mark_runtime_wc (struct azx*,struct azx_dev*,struct snd_pcm_substream*,int) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 

__attribute__((used)) static int substream_free_pages(struct azx *chip,
				struct snd_pcm_substream *substream)
{
	struct azx_dev *azx_dev = get_azx_dev(substream);
	mark_runtime_wc(chip, azx_dev, substream, false);
	return snd_pcm_lib_free_pages(substream);
}
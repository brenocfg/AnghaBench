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
struct snd_intelhad {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  had_do_reset (struct snd_intelhad*) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct snd_intelhad* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int had_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_intelhad *intelhaddata;

	intelhaddata = snd_pcm_substream_chip(substream);
	had_do_reset(intelhaddata);

	return snd_pcm_lib_free_pages(substream);
}
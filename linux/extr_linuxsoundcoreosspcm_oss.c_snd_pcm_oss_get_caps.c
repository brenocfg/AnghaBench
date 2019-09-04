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
struct snd_pcm_oss_file {struct snd_pcm_substream** streams; } ;

/* Variables and functions */
 int DSP_CAP_DUPLEX ; 
 int DSP_CAP_MMAP ; 
 int DSP_CAP_REALTIME ; 
 int DSP_CAP_TRIGGER ; 
 int snd_pcm_oss_get_caps1 (struct snd_pcm_substream*,int) ; 

__attribute__((used)) static int snd_pcm_oss_get_caps(struct snd_pcm_oss_file *pcm_oss_file)
{
	int result, idx;
	
	result = DSP_CAP_TRIGGER | DSP_CAP_MMAP	| DSP_CAP_DUPLEX | DSP_CAP_REALTIME;
	for (idx = 0; idx < 2; idx++) {
		struct snd_pcm_substream *substream = pcm_oss_file->streams[idx];
		result = snd_pcm_oss_get_caps1(substream, result);
	}
	result |= 0x0001;	/* revision - same as SB AWE 64 */
	return result;
}
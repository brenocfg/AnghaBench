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
struct rme32 {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ RME32_IO_DATA_BUFFER ; 
 int /*<<< orphan*/  memcpy_fromio (void*,scalar_t__,unsigned long) ; 
 struct rme32* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_rme32_capture_copy_kernel(struct snd_pcm_substream *substream,
					 int channel, unsigned long pos,
					 void *dst, unsigned long count)
{
	struct rme32 *rme32 = snd_pcm_substream_chip(substream);

	memcpy_fromio(dst, rme32->iobase + RME32_IO_DATA_BUFFER + pos, count);
	return 0;
}
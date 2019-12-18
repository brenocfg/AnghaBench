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
struct snd_usb_substream {int dummy; } ;
struct snd_pcm {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int snd_media_stream_init(struct snd_usb_substream *subs,
					struct snd_pcm *pcm, int stream)
						{ return 0; }
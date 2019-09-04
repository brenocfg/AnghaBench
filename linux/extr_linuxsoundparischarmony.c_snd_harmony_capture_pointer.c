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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int dummy; } ;
struct TYPE_4__ {unsigned long addr; unsigned long size; } ;
struct TYPE_3__ {int /*<<< orphan*/  capturing; } ;
struct snd_harmony {TYPE_2__ cbuf; int /*<<< orphan*/ * csubs; TYPE_1__ st; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  HARMONY_RCURADD ; 
 int /*<<< orphan*/  bytes_to_frames (struct snd_pcm_runtime*,unsigned long) ; 
 unsigned long harmony_read (struct snd_harmony*,int /*<<< orphan*/ ) ; 
 struct snd_harmony* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_harmony_capture_pointer(struct snd_pcm_substream *ss)
{
        struct snd_pcm_runtime *rt = ss->runtime;
        struct snd_harmony *h = snd_pcm_substream_chip(ss);
        unsigned long rcuradd;
        unsigned long caught;

        if (!(h->st.capturing) || (h->csubs == NULL))
                return 0;

        if ((h->cbuf.addr == 0) || (h->cbuf.size == 0))
                return 0;

        rcuradd = harmony_read(h, HARMONY_RCURADD);
        caught = rcuradd - h->cbuf.addr;

#ifdef HARMONY_DEBUG
        printk(KERN_DEBUG PFX "capture_pointer is 0x%lx-0x%lx = %d bytes\n",
               rcuradd, h->cbuf.addr, caught);
#endif

        if (rcuradd > h->cbuf.addr + h->cbuf.size) {
		return 0;
	}

        return bytes_to_frames(rt, caught);
}
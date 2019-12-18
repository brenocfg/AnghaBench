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
struct snd_pcm_substream {size_t stream; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dummy_page ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *dummy_pcm_page(struct snd_pcm_substream *substream,
				   unsigned long offset)
{
	return virt_to_page(dummy_page[substream->stream]); /* the same page */
}
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
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 size_t params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,size_t) ; 

__attribute__((used)) static int snd_ps3_pcm_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *hw_params)
{
	size_t size;

	/* alloc transport buffer */
	size = params_buffer_bytes(hw_params);
	snd_pcm_lib_malloc_pages(substream, size);
	return 0;
}
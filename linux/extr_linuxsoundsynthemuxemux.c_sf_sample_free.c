#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_util_memhdr {int dummy; } ;
struct snd_sf_sample {int dummy; } ;
struct TYPE_2__ {int (* sample_free ) (struct snd_emux*,struct snd_sf_sample*,struct snd_util_memhdr*) ;} ;
struct snd_emux {TYPE_1__ ops; } ;

/* Variables and functions */
 int stub1 (struct snd_emux*,struct snd_sf_sample*,struct snd_util_memhdr*) ; 

__attribute__((used)) static int sf_sample_free(void *private_data, struct snd_sf_sample *sp,
				   struct snd_util_memhdr *hdr)
{
	struct snd_emux *emu = private_data;
	return emu->ops.sample_free(emu, sp, hdr);
	
}
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
struct nuc900_audio {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ ACTL_ACIS0 ; 
 int AUDIO_READ (scalar_t__) ; 
 int CODEC_READY ; 
 int EPERM ; 
 struct nuc900_audio* nuc900_ac97_data ; 

__attribute__((used)) static int nuc900_checkready(void)
{
	struct nuc900_audio *nuc900_audio = nuc900_ac97_data;

	if (!(AUDIO_READ(nuc900_audio->mmio + ACTL_ACIS0) & CODEC_READY))
		return -EPERM;

	return 0;
}
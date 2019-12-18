#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int externalsr; } ;
struct TYPE_5__ {int sfreq; } ;
struct TYPE_7__ {TYPE_2__ aac_params; TYPE_1__ pcm_params; } ;
struct TYPE_8__ {TYPE_3__ uc; } ;
struct snd_sst_params {int codec; TYPE_4__ sparams; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SST_CODEC_TYPE_AAC 130 
#define  SST_CODEC_TYPE_MP3 129 
#define  SST_CODEC_TYPE_PCM 128 

int sst_get_sfreq(struct snd_sst_params *str_param)
{
	switch (str_param->codec) {
	case SST_CODEC_TYPE_PCM:
		return str_param->sparams.uc.pcm_params.sfreq;
	case SST_CODEC_TYPE_AAC:
		return str_param->sparams.uc.aac_params.externalsr;
	case SST_CODEC_TYPE_MP3:
		return 0;
	default:
		return -EINVAL;
	}
}
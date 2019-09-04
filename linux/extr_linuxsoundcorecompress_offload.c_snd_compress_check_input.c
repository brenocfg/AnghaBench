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
struct TYPE_3__ {scalar_t__ id; scalar_t__ ch_in; scalar_t__ ch_out; } ;
struct TYPE_4__ {int fragment_size; int fragments; } ;
struct snd_compr_params {TYPE_1__ codec; TYPE_2__ buffer; } ;

/* Variables and functions */
 int EINVAL ; 
 int INT_MAX ; 
 scalar_t__ SND_AUDIOCODEC_MAX ; 

__attribute__((used)) static int snd_compress_check_input(struct snd_compr_params *params)
{
	/* first let's check the buffer parameter's */
	if (params->buffer.fragment_size == 0 ||
	    params->buffer.fragments > INT_MAX / params->buffer.fragment_size ||
	    params->buffer.fragments == 0)
		return -EINVAL;

	/* now codec parameters */
	if (params->codec.id == 0 || params->codec.id > SND_AUDIOCODEC_MAX)
		return -EINVAL;

	if (params->codec.ch_in == 0 || params->codec.ch_out == 0)
		return -EINVAL;

	return 0;
}
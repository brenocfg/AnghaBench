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
struct snd_pcm_runtime {int dummy; } ;
struct amdtp_stream {int dummy; } ;

/* Variables and functions */
 int amdtp_stream_add_pcm_hw_constraints (struct amdtp_stream*,struct snd_pcm_runtime*) ; 
 int snd_pcm_hw_constraint_msbits (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 

int amdtp_dot_add_pcm_hw_constraints(struct amdtp_stream *s,
				     struct snd_pcm_runtime *runtime)
{
	int err;

	/* This protocol delivers 24 bit data in 32bit data channel. */
	err = snd_pcm_hw_constraint_msbits(runtime, 0, 32, 24);
	if (err < 0)
		return err;

	return amdtp_stream_add_pcm_hw_constraints(s, runtime);
}
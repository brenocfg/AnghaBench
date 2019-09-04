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
typedef  int uint_fast32_t ;
typedef  enum speaker_layout { ____Placeholder_speaker_layout } speaker_layout ;

/* Variables and functions */
 int SPEAKERS_2POINT1 ; 
 int SPEAKERS_4POINT1 ; 
 int SPEAKERS_5POINT1 ; 
 int SPEAKERS_7POINT1 ; 
 int SPEAKERS_MONO ; 
 int SPEAKERS_STEREO ; 
 int SPEAKERS_UNKNOWN ; 

__attribute__((used)) static enum speaker_layout jack_channels_to_obs_speakers(uint_fast32_t channels)
{
	switch(channels) {
	case 1: return SPEAKERS_MONO;
	case 2: return SPEAKERS_STEREO;
	case 3: return SPEAKERS_2POINT1;
	case 5: return SPEAKERS_4POINT1;
	case 6: return SPEAKERS_5POINT1;
	/* What should we do with 7 channels? */
	/* case 7: return SPEAKERS_...; */
	case 8: return SPEAKERS_7POINT1;
	}

	return SPEAKERS_UNKNOWN;
}
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
typedef  int uint32_t ;
typedef  enum speaker_layout { ____Placeholder_speaker_layout } speaker_layout ;

/* Variables and functions */
#define  SPEAKERS_2POINT1 135 
#define  SPEAKERS_4POINT0 134 
#define  SPEAKERS_4POINT1 133 
#define  SPEAKERS_5POINT1 132 
#define  SPEAKERS_7POINT1 131 
#define  SPEAKERS_MONO 130 
#define  SPEAKERS_STEREO 129 
#define  SPEAKERS_UNKNOWN 128 

__attribute__((used)) static inline uint32_t get_audio_channels(enum speaker_layout speakers)
{
	switch (speakers) {
	case SPEAKERS_MONO:             return 1;
	case SPEAKERS_STEREO:           return 2;
	case SPEAKERS_2POINT1:          return 3;
	case SPEAKERS_4POINT0:          return 4;
	case SPEAKERS_4POINT1:          return 5;
	case SPEAKERS_5POINT1:          return 6;
	case SPEAKERS_7POINT1:          return 8;
	case SPEAKERS_UNKNOWN:          return 0;
	}

	return 0;
}
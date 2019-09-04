#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int channels; void** map; } ;
typedef  TYPE_1__ pa_channel_map ;
typedef  enum speaker_layout { ____Placeholder_speaker_layout } speaker_layout ;

/* Variables and functions */
 void* PA_CHANNEL_POSITION_FRONT_CENTER ; 
 void* PA_CHANNEL_POSITION_FRONT_LEFT ; 
 void* PA_CHANNEL_POSITION_FRONT_RIGHT ; 
 void* PA_CHANNEL_POSITION_LFE ; 
 void* PA_CHANNEL_POSITION_MONO ; 
 void* PA_CHANNEL_POSITION_REAR_CENTER ; 
 void* PA_CHANNEL_POSITION_REAR_LEFT ; 
 void* PA_CHANNEL_POSITION_REAR_RIGHT ; 
 void* PA_CHANNEL_POSITION_SIDE_LEFT ; 
 void* PA_CHANNEL_POSITION_SIDE_RIGHT ; 
#define  SPEAKERS_2POINT1 135 
#define  SPEAKERS_4POINT0 134 
#define  SPEAKERS_4POINT1 133 
#define  SPEAKERS_5POINT1 132 
#define  SPEAKERS_7POINT1 131 
#define  SPEAKERS_MONO 130 
#define  SPEAKERS_STEREO 129 
#define  SPEAKERS_UNKNOWN 128 

__attribute__((used)) static pa_channel_map pulseaudio_channel_map(enum speaker_layout layout)
{
	pa_channel_map ret;

	ret.map[0] = PA_CHANNEL_POSITION_FRONT_LEFT;
	ret.map[1] = PA_CHANNEL_POSITION_FRONT_RIGHT;
	ret.map[2] = PA_CHANNEL_POSITION_FRONT_CENTER;
	ret.map[3] = PA_CHANNEL_POSITION_LFE;
	ret.map[4] = PA_CHANNEL_POSITION_REAR_LEFT;
	ret.map[5] = PA_CHANNEL_POSITION_REAR_RIGHT;
	ret.map[6] = PA_CHANNEL_POSITION_SIDE_LEFT;
	ret.map[7] = PA_CHANNEL_POSITION_SIDE_RIGHT;

	switch (layout) {
	case SPEAKERS_MONO:
		ret.channels = 1;
		ret.map[0] = PA_CHANNEL_POSITION_MONO;
		break;

	case SPEAKERS_STEREO:
		ret.channels = 2;
		break;

	case SPEAKERS_2POINT1:
		ret.channels = 3;
		ret.map[2] = PA_CHANNEL_POSITION_LFE;
		break;

	case SPEAKERS_4POINT0:
		ret.channels = 4;
		ret.map[3] = PA_CHANNEL_POSITION_REAR_CENTER;
		break;

	case SPEAKERS_4POINT1:
		ret.channels = 5;
		ret.map[4] = PA_CHANNEL_POSITION_REAR_CENTER;
		break;

	case SPEAKERS_5POINT1:
		ret.channels = 6;
		break;

	case SPEAKERS_7POINT1:
		ret.channels = 8;
		break;

	case SPEAKERS_UNKNOWN:
	default:
		ret.channels = 0;
		break;
	}

	return ret;
}
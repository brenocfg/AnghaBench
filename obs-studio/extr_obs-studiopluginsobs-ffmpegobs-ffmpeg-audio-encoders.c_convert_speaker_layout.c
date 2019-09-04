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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  enum speaker_layout { ____Placeholder_speaker_layout } speaker_layout ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CH_LAYOUT_4POINT0 ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_4POINT1 ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_5POINT1_BACK ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_7POINT1 ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_SURROUND ; 
#define  SPEAKERS_2POINT1 135 
#define  SPEAKERS_4POINT0 134 
#define  SPEAKERS_4POINT1 133 
#define  SPEAKERS_5POINT1 132 
#define  SPEAKERS_7POINT1 131 
#define  SPEAKERS_MONO 130 
#define  SPEAKERS_STEREO 129 
#define  SPEAKERS_UNKNOWN 128 

__attribute__((used)) static inline uint64_t convert_speaker_layout(enum speaker_layout layout)
{
	switch (layout) {
	case SPEAKERS_UNKNOWN:          return 0;
	case SPEAKERS_MONO:             return AV_CH_LAYOUT_MONO;
	case SPEAKERS_STEREO:           return AV_CH_LAYOUT_STEREO;
	case SPEAKERS_2POINT1:          return AV_CH_LAYOUT_SURROUND;
	case SPEAKERS_4POINT0:          return AV_CH_LAYOUT_4POINT0;
	case SPEAKERS_4POINT1:          return AV_CH_LAYOUT_4POINT1;
	case SPEAKERS_5POINT1:          return AV_CH_LAYOUT_5POINT1_BACK;
	case SPEAKERS_7POINT1:          return AV_CH_LAYOUT_7POINT1;
	}

	/* shouldn't get here */
	return 0;
}
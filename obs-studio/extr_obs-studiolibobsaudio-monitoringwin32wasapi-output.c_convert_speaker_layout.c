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
typedef  enum speaker_layout { ____Placeholder_speaker_layout } speaker_layout ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int DWORD ;

/* Variables and functions */
#define  KSAUDIO_SPEAKER_2POINT1 132 
#define  KSAUDIO_SPEAKER_4POINT1 131 
#define  KSAUDIO_SPEAKER_5POINT1 130 
#define  KSAUDIO_SPEAKER_7POINT1 129 
#define  KSAUDIO_SPEAKER_SURROUND 128 
 int SPEAKERS_2POINT1 ; 
 int SPEAKERS_4POINT0 ; 
 int SPEAKERS_4POINT1 ; 
 int SPEAKERS_5POINT1 ; 
 int SPEAKERS_7POINT1 ; 

__attribute__((used)) static enum speaker_layout convert_speaker_layout(DWORD layout, WORD channels)
{
	switch (layout) {
	case KSAUDIO_SPEAKER_2POINT1:          return SPEAKERS_2POINT1;
	case KSAUDIO_SPEAKER_SURROUND:         return SPEAKERS_4POINT0;
	case KSAUDIO_SPEAKER_4POINT1:          return SPEAKERS_4POINT1;
	case KSAUDIO_SPEAKER_5POINT1:          return SPEAKERS_5POINT1;
	case KSAUDIO_SPEAKER_7POINT1:          return SPEAKERS_7POINT1;
	}

	return (enum speaker_layout)channels;
}
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
typedef  int uint16_t ;

/* Variables and functions */
#define  AC_HOME 140 
#define  AC_SEARCH 139 
#define  AL_EMAIL 138 
#define  AUDIO_MUTE 137 
#define  AUDIO_VOL_DOWN 136 
#define  AUDIO_VOL_UP 135 
#define  TRANSPORT_FAST_FORWARD 134 
#define  TRANSPORT_NEXT_TRACK 133 
#define  TRANSPORT_PLAY_PAUSE 132 
#define  TRANSPORT_PREV_TRACK 131 
#define  TRANSPORT_REWIND 130 
#define  TRANSPORT_STOP 129 
#define  TRANSPORT_STOP_EJECT 128 

__attribute__((used)) static uint16_t usage2bits(uint16_t usage)
{
    switch (usage) {
        case AC_HOME:                 return 0x01;
        case AL_EMAIL:                return 0x02;
        case AC_SEARCH:               return 0x04;
        //case AL_KBD_LAYOUT:         return 0x08;  // Apple virtual keybaord toggle
        case AUDIO_VOL_UP:            return 0x10;
        case AUDIO_VOL_DOWN:          return 0x20;
        case AUDIO_MUTE:              return 0x40;
        case TRANSPORT_PLAY_PAUSE:    return 0x80;
        case TRANSPORT_NEXT_TRACK:    return 0x100;
        case TRANSPORT_PREV_TRACK:    return 0x200;
        case TRANSPORT_STOP:          return 0x400;
        case TRANSPORT_STOP_EJECT:    return 0x800;
        case TRANSPORT_FAST_FORWARD:  return 0x1000;
        case TRANSPORT_REWIND:        return 0x2000;
        //case return 0x4000;   // Stop/eject
        //case return 0x8000;   // Internet browser
    };
    return 0;
}
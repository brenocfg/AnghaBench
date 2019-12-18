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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
#define  AC_BACK 150 
#define  AC_BOOKMARKS 149 
#define  AC_FORWARD 148 
#define  AC_HOME 147 
#define  AC_MINIMIZE 146 
#define  AC_REFRESH 145 
#define  AC_SEARCH 144 
#define  AC_STOP 143 
#define  AL_CALCULATOR 142 
#define  AL_CC_CONFIG 141 
#define  AL_EMAIL 140 
#define  AL_LOCAL_BROWSER 139 
#define  AL_LOCK 138 
#define  AUDIO_MUTE 137 
#define  AUDIO_VOL_DOWN 136 
#define  AUDIO_VOL_UP 135 
 int /*<<< orphan*/  MUX_FOOTER (int) ; 
 int /*<<< orphan*/  MUX_HEADER (int,int) ; 
#define  TRANSPORT_EJECT 134 
#define  TRANSPORT_NEXT_TRACK 133 
#define  TRANSPORT_PLAY_PAUSE 132 
#define  TRANSPORT_PREV_TRACK 131 
#define  TRANSPORT_RECORD 130 
#define  TRANSPORT_REWIND 129 
#define  TRANSPORT_STOP 128 
 int /*<<< orphan*/  iwrap_check_connection () ; 
 int /*<<< orphan*/  iwrap_connected () ; 
 int /*<<< orphan*/  xmit (int) ; 

__attribute__((used)) static void send_consumer(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    static uint16_t last_data = 0;
    uint8_t         bits1     = 0;
    uint8_t         bits2     = 0;
    uint8_t         bits3     = 0;

    if (!iwrap_connected() && !iwrap_check_connection()) return;
    if (data == last_data) return;
    last_data = data;

    // 3.10 HID raw mode(iWRAP_HID_Application_Note.pdf)
    switch (data) {
        case AUDIO_VOL_UP:
            bits1 = 0x01;
            break;
        case AUDIO_VOL_DOWN:
            bits1 = 0x02;
            break;
        case AUDIO_MUTE:
            bits1 = 0x04;
            break;
        case TRANSPORT_PLAY_PAUSE:
            bits1 = 0x08;
            break;
        case TRANSPORT_NEXT_TRACK:
            bits1 = 0x10;
            break;
        case TRANSPORT_PREV_TRACK:
            bits1 = 0x20;
            break;
        case TRANSPORT_STOP:
            bits1 = 0x40;
            break;
        case TRANSPORT_EJECT:
            bits1 = 0x80;
            break;
        case AL_EMAIL:
            bits2 = 0x01;
            break;
        case AC_SEARCH:
            bits2 = 0x02;
            break;
        case AC_BOOKMARKS:
            bits2 = 0x04;
            break;
        case AC_HOME:
            bits2 = 0x08;
            break;
        case AC_BACK:
            bits2 = 0x10;
            break;
        case AC_FORWARD:
            bits2 = 0x20;
            break;
        case AC_STOP:
            bits2 = 0x40;
            break;
        case AC_REFRESH:
            bits2 = 0x80;
            break;
        case AL_CC_CONFIG:
            bits3 = 0x01;
            break;
        case AL_CALCULATOR:
            bits3 = 0x04;
            break;
        case AL_LOCK:
            bits3 = 0x08;
            break;
        case AL_LOCAL_BROWSER:
            bits3 = 0x10;
            break;
        case AC_MINIMIZE:
            bits3 = 0x20;
            break;
        case TRANSPORT_RECORD:
            bits3 = 0x40;
            break;
        case TRANSPORT_REWIND:
            bits3 = 0x80;
            break;
    }

    MUX_HEADER(0x01, 0x07);
    xmit(0x9f);
    xmit(0x05);  // Length
    xmit(0xa1);  // DATA(Input)
    xmit(0x03);  // Report ID
    xmit(bits1);
    xmit(bits2);
    xmit(bits3);
    MUX_FOOTER(0x01);
#endif
}
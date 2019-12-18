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
typedef  int BYTE ;

/* Variables and functions */
 int const AUDIO_ELEMENTARY_STREAM ; 
 int MPEG_AUDIO_HEADER ; 
 int MPEG_NO_HEADER ; 
 int MPEG_SYSTEM_HEADER ; 
 int MPEG_VIDEO_HEADER ; 
 int const PACK_START_CODE ; 
 int const SEQUENCE_HEADER_CODE ; 
 int const VIDEO_ELEMENTARY_STREAM ; 

__attribute__((used)) static int MPEGSplitter_head_check(const BYTE *header)
{
    /* If this is a possible start code, check for a system or video header */
    if (header[0] == 0 && header[1] == 0 && header[2] == 1)
    {
        /* Check if we got a system or elementary stream start code */
        if (header[3] == PACK_START_CODE ||
            header[3] == VIDEO_ELEMENTARY_STREAM ||
            header[3] == AUDIO_ELEMENTARY_STREAM)
            return MPEG_SYSTEM_HEADER;

        /* Check for a MPEG video sequence start code */
        if (header[3] == SEQUENCE_HEADER_CODE)
            return MPEG_VIDEO_HEADER;
    }

    /* This should give a good guess if we have an MPEG audio header */
    if(header[0] == 0xff && ((header[1]>>5)&0x7) == 0x7 &&
       ((header[1]>>1)&0x3) != 0 && ((header[2]>>4)&0xf) != 0xf &&
       ((header[2]>>2)&0x3) != 0x3)
        return MPEG_AUDIO_HEADER;

    /* Nothing yet.. */
    return MPEG_NO_HEADER;
}
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

/* Variables and functions */
 int /*<<< orphan*/  RTMP_Log (int,char*,char*) ; 
 scalar_t__ RTMP_debuglevel ; 
 void** hexdig ; 

void RTMP_LogHex(int level, const uint8_t *data, unsigned long len)
{
    unsigned long i;
    char line[50], *ptr;

    if ( level > (int)RTMP_debuglevel )
        return;

    ptr = line;

    for(i=0; i<len; i++)
    {
        *ptr++ = hexdig[0x0f & (data[i] >> 4)];
        *ptr++ = hexdig[0x0f & data[i]];
        if ((i & 0x0f) == 0x0f)
        {
            *ptr = '\0';
            ptr = line;
            RTMP_Log(level, "%s", line);
        }
        else
        {
            *ptr++ = ' ';
        }
    }
    if (i & 0x0f)
    {
        *ptr = '\0';
        RTMP_Log(level, "%s", line);
    }
}
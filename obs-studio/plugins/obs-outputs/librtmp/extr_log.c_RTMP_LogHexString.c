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
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int BP_GRAPH ; 
 int BP_LEN ; 
 int BP_OFFSET ; 
 int /*<<< orphan*/  RTMP_Log (int,char*,char*) ; 
 scalar_t__ RTMP_debuglevel ; 
 char* hexdig ; 
 scalar_t__ isprint (int const) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 

void RTMP_LogHexString(int level, const uint8_t *data, unsigned long len)
{
#define BP_OFFSET 9
#define BP_GRAPH 60
#define BP_LEN	80
    char	line[BP_LEN];
    unsigned long i;

    if ( !data || level > (int)RTMP_debuglevel )
        return;

    /* in case len is zero */
    line[0] = '\0';

    for ( i = 0 ; i < len ; i++ )
    {
        int n = i % 16;
        unsigned off;

        if( !n )
        {
            if( i ) RTMP_Log( level, "%s", line );
            memset( line, ' ', sizeof(line)-2 );
            line[sizeof(line)-2] = '\0';

            off = i % 0x0ffffU;

            line[2] = hexdig[0x0f & (off >> 12)];
            line[3] = hexdig[0x0f & (off >>  8)];
            line[4] = hexdig[0x0f & (off >>  4)];
            line[5] = hexdig[0x0f & off];
            line[6] = ':';
        }

        off = BP_OFFSET + n*3 + ((n >= 8)?1:0);
        line[off] = hexdig[0x0f & ( data[i] >> 4 )];
        line[off+1] = hexdig[0x0f & data[i]];

        off = BP_GRAPH + n + ((n >= 8)?1:0);

        if ( isprint( data[i] ))
        {
            line[BP_GRAPH + n] = data[i];
        }
        else
        {
            line[BP_GRAPH + n] = '.';
        }
    }

    RTMP_Log( level, "%s", line );
}
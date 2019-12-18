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
typedef  int USHORT ;
typedef  int UCHAR ;
typedef  int* PCHAR ;

/* Variables and functions */

int ExtractName( PCHAR pBuffer, PCHAR pOutput, USHORT Offset, UCHAR Limit )
{
    int c = 0, d = 0, i = 0, j = 0, k = 0, l = 0, m = 0;

    i = Offset;

    /* If Limit == 0, then we assume "no" limit. */
    d = Limit;
    if( 0 == Limit ) d = 255;

    while( d > 0 )
    {
        l = pBuffer[i] & 0xFF;
        i += 1;
        if( !m ) c += 1;

        if( 0xC0 == l )
        {
            if( !m ) c += 1;
            m = 1;
            d += (255 - Limit);
            i = pBuffer[i];
        }
        else
        {
            for( j = 0; j < l; j += 1 )
            {
                pOutput[k] = pBuffer[i];

                i += 1;
                if( !m ) c += 1;
                k += 1;
                d -= 1;
            }

            d -= 1;

            if( !pBuffer[i] || (d < 1) ) break;

            pOutput[k] = '.';
            k += 1;
        }
    };

    if( !m )
    {
        if( !Limit ) c += 1;
    }

    pOutput[k] = '\0';

    return c;
}
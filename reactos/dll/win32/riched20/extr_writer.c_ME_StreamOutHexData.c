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
typedef  int UINT ;
typedef  int /*<<< orphan*/  ME_OutStream ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HEX_BYTES_PER_LINE ; 
 int /*<<< orphan*/  ME_StreamOutMove (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int min (int,int) ; 

__attribute__((used)) static BOOL
ME_StreamOutHexData(ME_OutStream *stream, const BYTE *data, UINT len)
{

    char line[HEX_BYTES_PER_LINE * 2 + 1];
    UINT size, i;
    static const char hex[] = "0123456789abcdef";

    while (len)
    {
        size = min( len, HEX_BYTES_PER_LINE );
        for (i = 0; i < size; i++)
        {
            line[i * 2] = hex[(*data >> 4) & 0xf];
            line[i * 2 + 1] = hex[*data & 0xf];
            data++;
        }
        line[size * 2] = '\n';
        if (!ME_StreamOutMove( stream, line, size * 2 + 1 ))
            return FALSE;
        len -= size;
    }
    return TRUE;
}
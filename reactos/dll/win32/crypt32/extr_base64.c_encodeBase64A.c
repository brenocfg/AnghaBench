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
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 void** b64 ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LONG encodeBase64A(const BYTE *in_buf, int in_len, LPCSTR sep,
 char* out_buf, DWORD *out_len)
{
    int div, i;
    const BYTE *d = in_buf;
    int bytes = (in_len*8 + 5)/6, pad_bytes = (bytes % 4) ? 4 - (bytes % 4) : 0;
    DWORD needed;
    LPSTR ptr;

    TRACE("bytes is %d, pad bytes is %d\n", bytes, pad_bytes);
    needed = bytes + pad_bytes;
    needed += (needed / 64 + (needed % 64 ? 1 : 0)) * strlen(sep);
    needed++;

    if (needed > *out_len)
    {
        *out_len = needed;
        return ERROR_INSUFFICIENT_BUFFER;
    }
    else
        *out_len = needed;

    /* Three bytes of input give 4 chars of output */
    div = in_len / 3;

    ptr = out_buf;
    i = 0;
    while (div > 0)
    {
        if (i && i % 64 == 0)
        {
            strcpy(ptr, sep);
            ptr += strlen(sep);
        }
        /* first char is the first 6 bits of the first byte*/
        *ptr++ = b64[ ( d[0] >> 2) & 0x3f ];
        /* second char is the last 2 bits of the first byte and the first 4
         * bits of the second byte */
        *ptr++ = b64[ ((d[0] << 4) & 0x30) | (d[1] >> 4 & 0x0f)];
        /* third char is the last 4 bits of the second byte and the first 2
         * bits of the third byte */
        *ptr++ = b64[ ((d[1] << 2) & 0x3c) | (d[2] >> 6 & 0x03)];
        /* fourth char is the remaining 6 bits of the third byte */
        *ptr++ = b64[   d[2]       & 0x3f];
        i += 4;
        d += 3;
        div--;
    }

    switch(pad_bytes)
    {
        case 1:
            /* first char is the first 6 bits of the first byte*/
            *ptr++ = b64[ ( d[0] >> 2) & 0x3f ];
            /* second char is the last 2 bits of the first byte and the first 4
             * bits of the second byte */
            *ptr++ = b64[ ((d[0] << 4) & 0x30) | (d[1] >> 4 & 0x0f)];
            /* third char is the last 4 bits of the second byte padded with
             * two zeroes */
            *ptr++ = b64[ ((d[1] << 2) & 0x3c) ];
            /* fourth char is a = to indicate one byte of padding */
            *ptr++ = '=';
            break;
        case 2:
            /* first char is the first 6 bits of the first byte*/
            *ptr++ = b64[ ( d[0] >> 2) & 0x3f ];
            /* second char is the last 2 bits of the first byte padded with
             * four zeroes*/
            *ptr++ = b64[ ((d[0] << 4) & 0x30)];
            /* third char is = to indicate padding */
            *ptr++ = '=';
            /* fourth char is = to indicate padding */
            *ptr++ = '=';
            break;
    }
    strcpy(ptr, sep);

    return ERROR_SUCCESS;
}
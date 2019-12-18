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
typedef  int /*<<< orphan*/  SECURITY_STATUS ;
typedef  int* PBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_E_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  SEC_E_OK ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 char* b64 ; 

SECURITY_STATUS encodeBase64(PBYTE in_buf, int in_len, char* out_buf,
        int max_len, int *out_len)
{
    int div, i;
    PBYTE d = in_buf;
    int bytes = (in_len*8 + 5)/6, pad_bytes = (bytes % 4) ? 4 - (bytes % 4) : 0;

    TRACE("bytes is %d, pad bytes is %d\n", bytes, pad_bytes);
    *out_len = bytes + pad_bytes;

    if(bytes + pad_bytes + 1 > max_len)
        return SEC_E_BUFFER_TOO_SMALL;

    /* Three bytes of input give 4 chars of output */
    div = in_len / 3;

    i = 0;
    while(div > 0)
    {
        /* first char is the first 6 bits of the first byte*/
        out_buf[i + 0] = b64[ ( d[0] >> 2) & 0x3f ];
        /* second char is the last 2 bits of the first byte and the first 4
         * bits of the second byte */
        out_buf[i + 1] = b64[ ((d[0] << 4) & 0x30) | (d[1] >> 4 & 0x0f)];
        /* third char is the last 4 bits of the second byte and the first 2
         * bits of the third byte */
        out_buf[i + 2] = b64[ ((d[1] << 2) & 0x3c) | (d[2] >> 6 & 0x03)];
        /* fourth char is the remaining 6 bits of the third byte */
        out_buf[i + 3] = b64[   d[2]       & 0x3f];
        i += 4;
        d += 3;
        div--;
    }

    switch(pad_bytes)
    {
        case 1:
            /* first char is the first 6 bits of the first byte*/
            out_buf[i + 0] = b64[ ( d[0] >> 2) & 0x3f ];
            /* second char is the last 2 bits of the first byte and the first 4
             * bits of the second byte */
            out_buf[i + 1] = b64[ ((d[0] << 4) & 0x30) | (d[1] >> 4 & 0x0f)];
            /* third char is the last 4 bits of the second byte padded with
             * two zeroes */
            out_buf[i + 2] = b64[ ((d[1] << 2) & 0x3c) ];
            /* fourth char is a = to indicate one byte of padding */
            out_buf[i + 3] = '=';
            out_buf[i + 4] = 0;
            break;
        case 2:
            /* first char is the first 6 bits of the first byte*/
            out_buf[i + 0] = b64[ ( d[0] >> 2) & 0x3f ];
            /* second char is the last 2 bits of the first byte padded with
             * four zeroes*/
            out_buf[i + 1] = b64[ ((d[0] << 4) & 0x30)];
            /* third char is = to indicate padding */
            out_buf[i + 2] = '=';
            /* fourth char is = to indicate padding */
            out_buf[i + 3] = '=';
            out_buf[i + 4] = 0;
            break;
        default:
            out_buf[i] = 0;
    }

    return SEC_E_OK;
}
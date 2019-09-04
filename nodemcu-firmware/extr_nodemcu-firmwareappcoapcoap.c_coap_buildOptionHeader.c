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
typedef  int uint32_t ;

/* Variables and functions */
 int COAP_ERR_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  coap_option_nibble (size_t,int*) ; 

int coap_buildOptionHeader(uint32_t optDelta, size_t length, uint8_t *buf, size_t buflen)
{
    int n = 0;
    uint8_t *p = buf;
    uint8_t len, delta = 0;

    if (buflen < 5)
        return COAP_ERR_BUFFER_TOO_SMALL;

    coap_option_nibble(optDelta, &delta);
    coap_option_nibble(length, &len);

    *p++ = (0xFF & (delta << 4 | len));
    n++;
    if (delta == 13)
    {
        *p++ = (optDelta - 13);
        n++;
    }
    else
    if (delta == 14)
    {
        *p++ = ((optDelta-269) >> 8);
        *p++ = (0xFF & (optDelta-269));
        n+=2;
    }
    if (len == 13)
    {
        *p++ = (length - 13);
        n++;
    }
    else
    if (len == 14)
    {
        *p++ = (length >> 8);
        *p++ = (0xFF & (length-269));
        n+=2;
    }
    return n;
}
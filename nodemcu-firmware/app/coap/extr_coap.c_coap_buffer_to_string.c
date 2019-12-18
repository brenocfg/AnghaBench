#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int len; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ coap_buffer_t ;

/* Variables and functions */
 int COAP_ERR_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

int coap_buffer_to_string(char *strbuf, size_t strbuflen, const coap_buffer_t *buf)
{
    if (buf->len+1 > strbuflen)
        return COAP_ERR_BUFFER_TOO_SMALL;
    memcpy(strbuf, buf->p, buf->len);
    strbuf[buf->len] = 0;
    return 0;
}
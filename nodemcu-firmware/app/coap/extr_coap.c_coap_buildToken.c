#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int tkl; } ;
typedef  TYPE_1__ coap_header_t ;
struct TYPE_6__ {int len; int /*<<< orphan*/  p; } ;
typedef  TYPE_2__ coap_buffer_t ;

/* Variables and functions */
 int COAP_ERR_BUFFER_TOO_SMALL ; 
 int COAP_ERR_UNSUPPORTED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int coap_buildToken(const coap_buffer_t *tokbuf, const coap_header_t *hdr, uint8_t *buf, size_t buflen)
{
    // inject token
    uint8_t *p;
    if (buflen < (4U + hdr->tkl))
        return COAP_ERR_BUFFER_TOO_SMALL;
    p = buf + 4;
    if ((hdr->tkl > 0) && (hdr->tkl != tokbuf->len))
        return COAP_ERR_UNSUPPORTED;

    if (hdr->tkl > 0)
        memcpy(p, tokbuf->p, hdr->tkl);

    // http://tools.ietf.org/html/rfc7252#section-3.1
    // inject options
    return hdr->tkl;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ curlen; scalar_t__ bitcount; } ;
typedef  TYPE_1__ TINF_DATA ;

/* Variables and functions */
 int TINF_DATA_ERROR ; 
 int TINF_DONE ; 
 int TINF_OK ; 
 int /*<<< orphan*/  TINF_PUT (TYPE_1__*,unsigned char) ; 
 int uzlib_get_byte (TYPE_1__*) ; 

__attribute__((used)) static int tinf_inflate_uncompressed_block(TINF_DATA *d)
{
    if (d->curlen == 0) {
        unsigned int length, invlength;

        /* get length */
        length = uzlib_get_byte(d);
        length += 256 * uzlib_get_byte(d);
        /* get one's complement of length */
        invlength = uzlib_get_byte(d);
        invlength += 256 * uzlib_get_byte(d);
        /* check length */
        if (length != (~invlength & 0x0000ffff)) return TINF_DATA_ERROR;

        /* increment length to properly return TINF_DONE below, without
           producing data at the same time */
        d->curlen = length + 1;

        /* make sure we start next block on a byte boundary */
        d->bitcount = 0;
    }

    if (--d->curlen == 0) {
        return TINF_DONE;
    }

    unsigned char c = uzlib_get_byte(d);
    TINF_PUT(d, c);
    return TINF_OK;
}
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
struct TYPE_5__ {int curlen; unsigned char* buf; int /*<<< orphan*/  X; int /*<<< orphan*/  chksum; } ;
typedef  TYPE_1__ md2_state ;

/* Variables and functions */
 int CRYPT_INVALID_ARG ; 
 int CRYPT_OK ; 
 int /*<<< orphan*/  md2_compress (TYPE_1__*) ; 
 int /*<<< orphan*/  md2_update_chksum (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 

int md2_done(md2_state * md2, unsigned char *hash)
{
    unsigned long i, k;

    if (md2->curlen >= sizeof(md2->buf)) {
       return CRYPT_INVALID_ARG;
    }

    /* pad the message */
    k = 16 - md2->curlen;
    for (i = md2->curlen; i < 16; i++) {
        md2->buf[i] = (unsigned char)k;
    }

    /* hash and update */
    md2_compress(md2);
    md2_update_chksum(md2);

    /* hash checksum */
    memcpy(md2->buf, md2->chksum, 16);
    md2_compress(md2);

    /* output is lower 16 bytes of X */
    memcpy(hash, md2->X, 16);

    return CRYPT_OK;
}
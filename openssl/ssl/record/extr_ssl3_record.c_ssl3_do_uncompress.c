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
struct TYPE_6__ {int /*<<< orphan*/  expand; } ;
struct TYPE_5__ {unsigned char* comp; unsigned char* data; int length; } ;
typedef  TYPE_1__ SSL3_RECORD ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int COMP_expand_block (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ OPENSSL_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL3_RT_MAX_ENCRYPTED_LENGTH ; 
 int /*<<< orphan*/  SSL3_RT_MAX_PLAIN_LENGTH ; 

int ssl3_do_uncompress(SSL *ssl, SSL3_RECORD *rr)
{
#ifndef OPENSSL_NO_COMP
    int i;

    if (rr->comp == NULL) {
        rr->comp = (unsigned char *)
            OPENSSL_malloc(SSL3_RT_MAX_ENCRYPTED_LENGTH);
    }
    if (rr->comp == NULL)
        return 0;

    /* TODO(size_t): Convert this call */
    i = COMP_expand_block(ssl->expand, rr->comp,
                          SSL3_RT_MAX_PLAIN_LENGTH, rr->data, (int)rr->length);
    if (i < 0)
        return 0;
    else
        rr->length = i;
    rr->data = rr->comp;
#endif
    return 1;
}
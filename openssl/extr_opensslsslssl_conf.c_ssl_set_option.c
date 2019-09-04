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
typedef  unsigned long uint32_t ;
struct TYPE_3__ {unsigned long* poptions; unsigned long* pcert_flags; unsigned long* pvfy_flags; } ;
typedef  TYPE_1__ SSL_CONF_CTX ;

/* Variables and functions */
#define  SSL_TFLAG_CERT 130 
 unsigned int SSL_TFLAG_INV ; 
#define  SSL_TFLAG_OPTION 129 
 unsigned int SSL_TFLAG_TYPE_MASK ; 
#define  SSL_TFLAG_VFY 128 

__attribute__((used)) static void ssl_set_option(SSL_CONF_CTX *cctx, unsigned int name_flags,
                           unsigned long option_value, int onoff)
{
    uint32_t *pflags;
    if (cctx->poptions == NULL)
        return;
    if (name_flags & SSL_TFLAG_INV)
        onoff ^= 1;
    switch (name_flags & SSL_TFLAG_TYPE_MASK) {

    case SSL_TFLAG_CERT:
        pflags = cctx->pcert_flags;
        break;

    case SSL_TFLAG_VFY:
        pflags = cctx->pvfy_flags;
        break;

    case SSL_TFLAG_OPTION:
        pflags = cctx->poptions;
        break;

    default:
        return;

    }
    if (onoff)
        *pflags |= option_value;
    else
        *pflags &= ~option_value;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int hash; int sig; int sigandhash; int sigalg; } ;
struct TYPE_6__ {TYPE_1__* cert; } ;
struct TYPE_5__ {scalar_t__ shared_sigalgslen; TYPE_3__** shared_sigalgs; } ;
typedef  TYPE_2__ SSL ;
typedef  TYPE_3__ SIGALG_LOOKUP ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 

int SSL_get_shared_sigalgs(SSL *s, int idx,
                           int *psign, int *phash, int *psignhash,
                           unsigned char *rsig, unsigned char *rhash)
{
    const SIGALG_LOOKUP *shsigalgs;
    if (s->cert->shared_sigalgs == NULL
        || idx < 0
        || idx >= (int)s->cert->shared_sigalgslen
        || s->cert->shared_sigalgslen > INT_MAX)
        return 0;
    shsigalgs = s->cert->shared_sigalgs[idx];
    if (phash != NULL)
        *phash = shsigalgs->hash;
    if (psign != NULL)
        *psign = shsigalgs->sig;
    if (psignhash != NULL)
        *psignhash = shsigalgs->sigandhash;
    if (rsig != NULL)
        *rsig = (unsigned char)(shsigalgs->sigalg & 0xff);
    if (rhash != NULL)
        *rhash = (unsigned char)((shsigalgs->sigalg >> 8) & 0xff);
    return (int)s->cert->shared_sigalgslen;
}
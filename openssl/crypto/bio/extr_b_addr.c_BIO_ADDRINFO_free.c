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
struct TYPE_5__ {struct TYPE_5__* bai_addr; struct TYPE_5__* bai_next; } ;
typedef  TYPE_1__ BIO_ADDRINFO ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 scalar_t__ _cond ; 
 int /*<<< orphan*/  freeaddrinfo (TYPE_1__*) ; 

void BIO_ADDRINFO_free(BIO_ADDRINFO *bai)
{
    if (bai == NULL)
        return;

#ifdef AI_PASSIVE
# ifdef AF_UNIX
#  define _cond bai->bai_family != AF_UNIX
# else
#  define _cond 1
# endif
    if (_cond) {
        freeaddrinfo(bai);
        return;
    }
#endif

    /* Free manually when we know that addrinfo_wrap() was used.
     * See further comment above addrinfo_wrap()
     */
    while (bai != NULL) {
        BIO_ADDRINFO *next = bai->bai_next;
        OPENSSL_free(bai->bai_addr);
        OPENSSL_free(bai);
        bai = next;
    }
}
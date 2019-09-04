#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bio_chain; struct TYPE_4__* cache_peer_serv; struct TYPE_4__* cache_peer_name; struct TYPE_4__* cache_accepting_serv; struct TYPE_4__* cache_accepting_name; int /*<<< orphan*/  addr_first; struct TYPE_4__* param_serv; struct TYPE_4__* param_addr; } ;
typedef  TYPE_1__ BIO_ACCEPT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ADDRINFO_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void BIO_ACCEPT_free(BIO_ACCEPT *a)
{
    if (a == NULL)
        return;
    OPENSSL_free(a->param_addr);
    OPENSSL_free(a->param_serv);
    BIO_ADDRINFO_free(a->addr_first);
    OPENSSL_free(a->cache_accepting_name);
    OPENSSL_free(a->cache_accepting_serv);
    OPENSSL_free(a->cache_peer_name);
    OPENSSL_free(a->cache_peer_serv);
    BIO_free(a->bio_chain);
    OPENSSL_free(a);
}
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
struct TYPE_3__ {int retval; scalar_t__ name; } ;
typedef  TYPE_1__ STRINT_PAIR ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int CERT_PKEY_SUITEB ; 
 int SSL_CERT_FLAG_SUITEB_128_LOS ; 
 int SSL_set_cert_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 TYPE_1__* chain_flags ; 

__attribute__((used)) static void print_chain_flags(SSL *s, int flags)
{
    STRINT_PAIR *pp;

    for (pp = chain_flags; pp->name; ++pp)
        BIO_printf(bio_err, "\t%s: %s\n",
                   pp->name,
                   (flags & pp->retval) ? "OK" : "NOT OK");
    BIO_printf(bio_err, "\tSuite B: ");
    if (SSL_set_cert_flags(s, 0) & SSL_CERT_FLAG_SUITEB_128_LOS)
        BIO_puts(bio_err, flags & CERT_PKEY_SUITEB ? "OK\n" : "NOT OK\n");
    else
        BIO_printf(bio_err, "not tested\n");
}
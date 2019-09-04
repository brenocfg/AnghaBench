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
struct TYPE_3__ {int mdpth; int pdpth; int /*<<< orphan*/ * mtlsa; int /*<<< orphan*/ * mcert; int /*<<< orphan*/ * certs; int /*<<< orphan*/ * trecs; } ;
typedef  TYPE_1__ SSL_DANE ;

/* Variables and functions */
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_X509_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  sk_danetls_record_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlsa_free ; 

__attribute__((used)) static void dane_final(SSL_DANE *dane)
{
    sk_danetls_record_pop_free(dane->trecs, tlsa_free);
    dane->trecs = NULL;

    sk_X509_pop_free(dane->certs, X509_free);
    dane->certs = NULL;

    X509_free(dane->mcert);
    dane->mcert = NULL;
    dane->mtlsa = NULL;
    dane->mdpth = -1;
    dane->pdpth = -1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_7__ {int mdpth; TYPE_1__* mtlsa; int /*<<< orphan*/ * mcert; } ;
struct TYPE_8__ {scalar_t__ verify_result; TYPE_2__ dane; } ;
struct TYPE_6__ {int /*<<< orphan*/ * spki; } ;
typedef  TYPE_2__ SSL_DANE ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  DANETLS_ENABLED (TYPE_2__*) ; 
 scalar_t__ X509_V_OK ; 

int SSL_get0_dane_authority(SSL *s, X509 **mcert, EVP_PKEY **mspki)
{
    SSL_DANE *dane = &s->dane;

    if (!DANETLS_ENABLED(dane) || s->verify_result != X509_V_OK)
        return -1;
    if (dane->mtlsa) {
        if (mcert)
            *mcert = dane->mcert;
        if (mspki)
            *mspki = (dane->mcert == NULL) ? dane->mtlsa->spki : NULL;
    }
    return dane->mdpth;
}
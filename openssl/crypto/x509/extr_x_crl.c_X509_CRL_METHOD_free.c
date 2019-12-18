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
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ X509_CRL_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int X509_CRL_METHOD_DYNAMIC ; 

void X509_CRL_METHOD_free(X509_CRL_METHOD *m)
{
    if (m == NULL || !(m->flags & X509_CRL_METHOD_DYNAMIC))
        return;
    OPENSSL_free(m);
}
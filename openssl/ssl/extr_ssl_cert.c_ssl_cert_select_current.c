#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_5__ {TYPE_1__* key; TYPE_1__* pkeys; } ;
struct TYPE_4__ {int /*<<< orphan*/ * x509; scalar_t__ privatekey; } ;
typedef  TYPE_1__ CERT_PKEY ;
typedef  TYPE_2__ CERT ;

/* Variables and functions */
 int SSL_PKEY_NUM ; 
 int /*<<< orphan*/  X509_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ssl_cert_select_current(CERT *c, X509 *x)
{
    int i;
    if (x == NULL)
        return 0;
    for (i = 0; i < SSL_PKEY_NUM; i++) {
        CERT_PKEY *cpk = c->pkeys + i;
        if (cpk->x509 == x && cpk->privatekey) {
            c->key = cpk;
            return 1;
        }
    }

    for (i = 0; i < SSL_PKEY_NUM; i++) {
        CERT_PKEY *cpk = c->pkeys + i;
        if (cpk->privatekey && cpk->x509 && !X509_cmp(cpk->x509, x)) {
            c->key = cpk;
            return 1;
        }
    }
    return 0;
}
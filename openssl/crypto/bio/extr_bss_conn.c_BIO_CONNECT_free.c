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
struct TYPE_4__ {int /*<<< orphan*/  addr_first; struct TYPE_4__* param_service; struct TYPE_4__* param_hostname; } ;
typedef  TYPE_1__ BIO_CONNECT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ADDRINFO_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void BIO_CONNECT_free(BIO_CONNECT *a)
{
    if (a == NULL)
        return;
    OPENSSL_free(a->param_hostname);
    OPENSSL_free(a->param_service);
    BIO_ADDRINFO_free(a->addr_first);
    OPENSSL_free(a);
}
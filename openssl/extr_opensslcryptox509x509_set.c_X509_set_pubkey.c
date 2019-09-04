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
struct TYPE_4__ {int /*<<< orphan*/  key; } ;
struct TYPE_5__ {TYPE_1__ cert_info; } ;
typedef  TYPE_2__ X509 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int X509_PUBKEY_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int X509_set_pubkey(X509 *x, EVP_PKEY *pkey)
{
    if (x == NULL)
        return 0;
    return X509_PUBKEY_set(&(x->cert_info.key), pkey);
}
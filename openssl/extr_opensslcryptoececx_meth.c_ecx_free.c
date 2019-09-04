#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  privkey; } ;
struct TYPE_6__ {TYPE_4__* ecx; } ;
struct TYPE_7__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  KEYLEN (TYPE_2__*) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_4__*) ; 
 int /*<<< orphan*/  OPENSSL_secure_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecx_free(EVP_PKEY *pkey)
{
    if (pkey->pkey.ecx != NULL)
        OPENSSL_secure_clear_free(pkey->pkey.ecx->privkey, KEYLEN(pkey));
    OPENSSL_free(pkey->pkey.ecx);
}
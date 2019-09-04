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
struct TYPE_4__ {int /*<<< orphan*/  rsa; } ;
struct TYPE_5__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int RSA_check_key_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rsa_pkey_check(const EVP_PKEY *pkey)
{
    return RSA_check_key_ex(pkey->pkey.rsa, NULL);
}
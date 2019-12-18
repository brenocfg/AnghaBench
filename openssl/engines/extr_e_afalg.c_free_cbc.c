#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * _hidden; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_meth_free (int /*<<< orphan*/ *) ; 
 unsigned short OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afalg_cipher_nids ; 
 TYPE_1__* cbc_handle ; 

__attribute__((used)) static int free_cbc(void)
{
    short unsigned int i;
    for(i = 0; i < OSSL_NELEM(afalg_cipher_nids); i++) {
        EVP_CIPHER_meth_free(cbc_handle[i]._hidden);
        cbc_handle[i]._hidden = NULL;
    }
    return 1;
}
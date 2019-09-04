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
struct TYPE_4__ {int pkey_id; int flags; } ;
typedef  TYPE_1__ EVP_PKEY_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_EVP_PKEY_METH_NEW ; 
 int EVP_PKEY_FLAG_DYNAMIC ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

EVP_PKEY_METHOD *EVP_PKEY_meth_new(int id, int flags)
{
    EVP_PKEY_METHOD *pmeth;

    pmeth = OPENSSL_zalloc(sizeof(*pmeth));
    if (pmeth == NULL) {
        EVPerr(EVP_F_EVP_PKEY_METH_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    pmeth->pkey_id = id;
    pmeth->flags = flags | EVP_PKEY_FLAG_DYNAMIC;
    return pmeth;
}
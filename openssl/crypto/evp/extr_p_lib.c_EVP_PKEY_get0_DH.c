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
struct TYPE_4__ {int /*<<< orphan*/ * dh; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  DH ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_GET0_DH ; 
 scalar_t__ EVP_PKEY_DH ; 
 scalar_t__ EVP_PKEY_DHX ; 
 int /*<<< orphan*/  EVP_R_EXPECTING_A_DH_KEY ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DH *EVP_PKEY_get0_DH(const EVP_PKEY *pkey)
{
    if (pkey->type != EVP_PKEY_DH && pkey->type != EVP_PKEY_DHX) {
        EVPerr(EVP_F_EVP_PKEY_GET0_DH, EVP_R_EXPECTING_A_DH_KEY);
        return NULL;
    }
    return pkey->pkey.dh;
}
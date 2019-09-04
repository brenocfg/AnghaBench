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
struct TYPE_4__ {int type; } ;
typedef  TYPE_1__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_SET_ALIAS_TYPE ; 
 scalar_t__ EVP_PKEY_base_id (TYPE_1__*) ; 
 scalar_t__ EVP_PKEY_type (int) ; 
 int /*<<< orphan*/  EVP_R_UNSUPPORTED_ALGORITHM ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int EVP_PKEY_set_alias_type(EVP_PKEY *pkey, int type)
{
    if (pkey->type == type) {
        return 1; /* it already is that type */
    }

    /*
     * The application is requesting to alias this to a different pkey type,
     * but not one that resolves to the base type.
     */
    if (EVP_PKEY_type(type) != EVP_PKEY_base_id(pkey)) {
        EVPerr(EVP_F_EVP_PKEY_SET_ALIAS_TYPE, EVP_R_UNSUPPORTED_ALGORITHM);
        return 0;
    }

    pkey->type = type;
    return 1;
}
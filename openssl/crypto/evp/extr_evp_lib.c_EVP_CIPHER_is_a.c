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
struct TYPE_4__ {int /*<<< orphan*/  name_id; int /*<<< orphan*/ * prov; } ;
typedef  TYPE_1__ EVP_CIPHER ;

/* Variables and functions */
 int EVP_CIPHER_nid (TYPE_1__ const*) ; 
 int OBJ_ln2nid (char const*) ; 
 int OBJ_sn2nid (char const*) ; 
 int evp_is_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

int EVP_CIPHER_is_a(const EVP_CIPHER *cipher, const char *name)
{
#ifndef FIPS_MODE
    if (cipher->prov == NULL) {
        int nid = EVP_CIPHER_nid(cipher);

        return nid == OBJ_sn2nid(name) || nid == OBJ_ln2nid(name);
    }
#endif
    return evp_is_a(cipher->prov, cipher->name_id, name);
}
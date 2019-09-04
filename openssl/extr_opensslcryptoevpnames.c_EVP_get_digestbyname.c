#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_NAME_TYPE_MD_METH ; 
 scalar_t__ OBJ_NAME_get (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_INIT_ADD_ALL_DIGESTS ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const EVP_MD *EVP_get_digestbyname(const char *name)
{
    const EVP_MD *cp;

    if (!OPENSSL_init_crypto(OPENSSL_INIT_ADD_ALL_DIGESTS, NULL))
        return NULL;

    cp = (const EVP_MD *)OBJ_NAME_get(name, OBJ_NAME_TYPE_MD_METH);
    return cp;
}
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
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OSSL_NAMEMAP ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int ossl_namemap_name2num (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * ossl_namemap_stored (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_provider_library_context (int /*<<< orphan*/ *) ; 

int evp_is_a(OSSL_PROVIDER *prov, int number, const char *name)
{
    OPENSSL_CTX *libctx = ossl_provider_library_context(prov);
    OSSL_NAMEMAP *namemap = ossl_namemap_stored(libctx);

    return ossl_namemap_name2num(namemap, name) == number;
}
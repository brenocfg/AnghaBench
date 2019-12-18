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
 int /*<<< orphan*/  ossl_namemap_doall_names (int /*<<< orphan*/ *,int,void (*) (char const*,void*),void*) ; 
 int /*<<< orphan*/ * ossl_namemap_stored (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_provider_library_context (int /*<<< orphan*/ *) ; 

void evp_names_do_all(OSSL_PROVIDER *prov, int number,
                      void (*fn)(const char *name, void *data),
                      void *data)
{
    OPENSSL_CTX *libctx = ossl_provider_library_context(prov);
    OSSL_NAMEMAP *namemap = ossl_namemap_stored(libctx);

    ossl_namemap_doall_names(namemap, number, fn, data);
}
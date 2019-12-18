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
 char const* ossl_namemap_num2name (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ossl_namemap_stored (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_provider_library_context (int /*<<< orphan*/ *) ; 

const char *evp_first_name(OSSL_PROVIDER *prov, int name_id)
{
    OPENSSL_CTX *libctx = ossl_provider_library_context(prov);
    OSSL_NAMEMAP *namemap = ossl_namemap_stored(libctx);

    return ossl_namemap_num2name(namemap, name_id, 0);
}
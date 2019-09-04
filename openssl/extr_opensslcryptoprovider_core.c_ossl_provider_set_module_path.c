#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * path; } ;
typedef  TYPE_1__ OSSL_PROVIDER ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_OSSL_PROVIDER_SET_MODULE_PATH ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char const*) ; 

int ossl_provider_set_module_path(OSSL_PROVIDER *prov, const char *module_path)
{
    OPENSSL_free(prov->path);
    if (module_path == NULL)
        return 1;
    if ((prov->path = OPENSSL_strdup(module_path)) != NULL)
        return 1;
    CRYPTOerr(CRYPTO_F_OSSL_PROVIDER_SET_MODULE_PATH, ERR_R_MALLOC_FAILURE);
    return 0;
}
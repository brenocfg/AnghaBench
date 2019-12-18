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

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * OSSL_PROVIDER_load (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  OSSL_PROVIDER_unload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static int load_fips_prov_and_run_self_test(const char *prov_name)
{
    int ret = 0;
    OSSL_PROVIDER *prov = NULL;

    prov = OSSL_PROVIDER_load(NULL, prov_name);
    if (prov == NULL) {
        BIO_printf(bio_err, "Failed to load FIPS module\n");
        goto end;
    }
    ret = 1;
end:
    OSSL_PROVIDER_unload(prov);
    return ret;
}
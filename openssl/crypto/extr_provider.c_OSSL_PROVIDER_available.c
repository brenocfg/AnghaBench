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
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int ossl_provider_available (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_provider_find (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_provider_free (int /*<<< orphan*/ *) ; 

int OSSL_PROVIDER_available(OPENSSL_CTX *libctx, const char *name)
{
    OSSL_PROVIDER *prov = NULL;
    int available = 0;

    /* Find it or create it */
    prov = ossl_provider_find(libctx, name, 0);
    available = ossl_provider_available(prov);
    ossl_provider_free(prov);
    return available;
}
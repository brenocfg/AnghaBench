#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* data; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ KDF_DATA ;
typedef  TYPE_2__ EVP_TEST ;
typedef  int /*<<< orphan*/  EVP_KDF ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_KDF_CTX_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_get_kdfbyname (char const*) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 

__attribute__((used)) static int kdf_test_init(EVP_TEST *t, const char *name)
{
    KDF_DATA *kdata;
    const EVP_KDF *kdf;

#ifdef OPENSSL_NO_SCRYPT
    if (strcmp(name, "scrypt") == 0) {
        t->skip = 1;
        return 1;
    }
#endif

    kdf = EVP_get_kdfbyname(name);
    if (kdf == NULL)
        return 0;

    if (!TEST_ptr(kdata = OPENSSL_zalloc(sizeof(*kdata))))
        return 0;
    kdata->ctx = EVP_KDF_CTX_new(kdf);
    if (kdata->ctx == NULL) {
        OPENSSL_free(kdata);
        return 0;
    }
    t->data = kdata;
    return 1;
}
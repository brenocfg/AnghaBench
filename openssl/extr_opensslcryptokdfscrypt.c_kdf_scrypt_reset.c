#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pass_len; int /*<<< orphan*/  pass; int /*<<< orphan*/  salt; } ;
typedef  TYPE_1__ EVP_KDF_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdf_scrypt_init (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kdf_scrypt_reset(EVP_KDF_IMPL *impl)
{
    OPENSSL_free(impl->salt);
    OPENSSL_clear_free(impl->pass, impl->pass_len);
    memset(impl, 0, sizeof(*impl));
    kdf_scrypt_init(impl);
}
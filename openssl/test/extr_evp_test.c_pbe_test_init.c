#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int skip; TYPE_1__* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  pbe_type; } ;
typedef  int /*<<< orphan*/  PBE_TYPE ;
typedef  TYPE_1__ PBE_DATA ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  PBE_TYPE_INVALID ; 
 int /*<<< orphan*/  PBE_TYPE_PBKDF2 ; 
 int /*<<< orphan*/  PBE_TYPE_PKCS12 ; 
 int /*<<< orphan*/  PBE_TYPE_SCRYPT ; 
 int /*<<< orphan*/  TEST_error (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pbe_test_init(EVP_TEST *t, const char *alg)
{
    PBE_DATA *pdat;
    PBE_TYPE pbe_type = PBE_TYPE_INVALID;

    if (strcmp(alg, "scrypt") == 0) {
#ifndef OPENSSL_NO_SCRYPT
        pbe_type = PBE_TYPE_SCRYPT;
#else
        t->skip = 1;
        return 1;
#endif
    } else if (strcmp(alg, "pbkdf2") == 0) {
        pbe_type = PBE_TYPE_PBKDF2;
    } else if (strcmp(alg, "pkcs12") == 0) {
        pbe_type = PBE_TYPE_PKCS12;
    } else {
        TEST_error("Unknown pbe algorithm %s", alg);
    }
    pdat = OPENSSL_zalloc(sizeof(*pdat));
    pdat->pbe_type = pbe_type;
    t->data = pdat;
    return 1;
}
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
typedef  int /*<<< orphan*/  epilogue ;
struct TYPE_6__ {int skip; TYPE_1__* data; } ;
struct TYPE_5__ {int type; int /*<<< orphan*/  controls; int /*<<< orphan*/ * mac; int /*<<< orphan*/  mac_name; } ;
typedef  TYPE_1__ MAC_DATA ;
typedef  TYPE_2__ EVP_TEST ;
typedef  int /*<<< orphan*/  EVP_MAC ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_MAC_fetch (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int EVP_PKEY_CMAC ; 
 int EVP_PKEY_HMAC ; 
 int EVP_PKEY_POLY1305 ; 
 int EVP_PKEY_SIPHASH ; 
 int NID_undef ; 
 int OBJ_ln2nid (char const*) ; 
 int OBJ_sn2nid (char const*) ; 
 int /*<<< orphan*/  OPENSSL_strdup (char const*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  sk_OPENSSL_STRING_new_null () ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static int mac_test_init(EVP_TEST *t, const char *alg)
{
    EVP_MAC *mac = NULL;
    int type = NID_undef;
    MAC_DATA *mdat;

    if ((mac = EVP_MAC_fetch(NULL, alg, NULL)) == NULL) {
        /*
         * Since we didn't find an EVP_MAC, we check for known EVP_PKEY methods
         * For debugging purposes, we allow 'NNNN by EVP_PKEY' to force running
         * the EVP_PKEY method.
         */
        size_t sz = strlen(alg);
        static const char epilogue[] = " by EVP_PKEY";

        if (sz >= sizeof(epilogue)
            && strcmp(alg + sz - (sizeof(epilogue) - 1), epilogue) == 0)
            sz -= sizeof(epilogue) - 1;

        if (strncmp(alg, "HMAC", sz) == 0) {
            type = EVP_PKEY_HMAC;
        } else if (strncmp(alg, "CMAC", sz) == 0) {
#ifndef OPENSSL_NO_CMAC
            type = EVP_PKEY_CMAC;
#else
            t->skip = 1;
            return 1;
#endif
        } else if (strncmp(alg, "Poly1305", sz) == 0) {
#ifndef OPENSSL_NO_POLY1305
            type = EVP_PKEY_POLY1305;
#else
            t->skip = 1;
            return 1;
#endif
        } else if (strncmp(alg, "SipHash", sz) == 0) {
#ifndef OPENSSL_NO_SIPHASH
            type = EVP_PKEY_SIPHASH;
#else
            t->skip = 1;
            return 1;
#endif
        } else {
            /*
             * Not a known EVP_PKEY method either.  If it's a known OID, then
             * assume it's been disabled.
             */
            if (OBJ_sn2nid(alg) != NID_undef || OBJ_ln2nid(alg) != NID_undef) {
                t->skip = 1;
                return 1;
            }

            return 0;
        }
    }

    mdat = OPENSSL_zalloc(sizeof(*mdat));
    mdat->type = type;
    mdat->mac_name = OPENSSL_strdup(alg);
    mdat->mac = mac;
    mdat->controls = sk_OPENSSL_STRING_new_null();
    t->data = mdat;
    return 1;
}
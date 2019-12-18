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
typedef  int /*<<< orphan*/  OSSL_ALGORITHM ;

/* Variables and functions */
#define  OSSL_OP_CIPHER 134 
#define  OSSL_OP_DIGEST 133 
#define  OSSL_OP_KDF 132 
#define  OSSL_OP_KEYEXCH 131 
#define  OSSL_OP_KEYMGMT 130 
#define  OSSL_OP_MAC 129 
#define  OSSL_OP_SIGNATURE 128 
 int /*<<< orphan*/  const* deflt_ciphers ; 
 int /*<<< orphan*/  const* deflt_digests ; 
 int /*<<< orphan*/  const* deflt_kdfs ; 
 int /*<<< orphan*/  const* deflt_keyexch ; 
 int /*<<< orphan*/  const* deflt_keymgmt ; 
 int /*<<< orphan*/  const* deflt_macs ; 
 int /*<<< orphan*/  const* deflt_signature ; 

__attribute__((used)) static const OSSL_ALGORITHM *deflt_query(OSSL_PROVIDER *prov,
                                         int operation_id,
                                         int *no_cache)
{
    *no_cache = 0;
    switch (operation_id) {
    case OSSL_OP_DIGEST:
        return deflt_digests;
    case OSSL_OP_CIPHER:
        return deflt_ciphers;
    case OSSL_OP_MAC:
        return deflt_macs;
    case OSSL_OP_KDF:
        return deflt_kdfs;
    case OSSL_OP_KEYMGMT:
        return deflt_keymgmt;
    case OSSL_OP_KEYEXCH:
        return deflt_keyexch;
    case OSSL_OP_SIGNATURE:
        return deflt_signature;
    }
    return NULL;
}
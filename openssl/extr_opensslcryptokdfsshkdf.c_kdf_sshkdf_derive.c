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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  session_id_len; int /*<<< orphan*/ * session_id; int /*<<< orphan*/  xcghash_len; int /*<<< orphan*/ * xcghash; int /*<<< orphan*/  key_len; int /*<<< orphan*/ * key; int /*<<< orphan*/ * md; } ;
typedef  TYPE_1__ EVP_KDF_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  KDF_F_KDF_SSHKDF_DERIVE ; 
 int /*<<< orphan*/  KDF_R_MISSING_KEY ; 
 int /*<<< orphan*/  KDF_R_MISSING_MESSAGE_DIGEST ; 
 int /*<<< orphan*/  KDF_R_MISSING_SESSION_ID ; 
 int /*<<< orphan*/  KDF_R_MISSING_TYPE ; 
 int /*<<< orphan*/  KDF_R_MISSING_XCGHASH ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SSHKDF (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,unsigned char*,size_t) ; 

__attribute__((used)) static int kdf_sshkdf_derive(EVP_KDF_IMPL *impl, unsigned char *key,
                             size_t keylen)
{
    if (impl->md == NULL) {
        KDFerr(KDF_F_KDF_SSHKDF_DERIVE, KDF_R_MISSING_MESSAGE_DIGEST);
        return 0;
    }
    if (impl->key == NULL) {
        KDFerr(KDF_F_KDF_SSHKDF_DERIVE, KDF_R_MISSING_KEY);
        return 0;
    }
    if (impl->xcghash == NULL) {
        KDFerr(KDF_F_KDF_SSHKDF_DERIVE, KDF_R_MISSING_XCGHASH);
        return 0;
    }
    if (impl->session_id == NULL) {
        KDFerr(KDF_F_KDF_SSHKDF_DERIVE, KDF_R_MISSING_SESSION_ID);
        return 0;
    }
    if (impl->type == 0) {
        KDFerr(KDF_F_KDF_SSHKDF_DERIVE, KDF_R_MISSING_TYPE);
        return 0;
    }
    return SSHKDF(impl->md, impl->key, impl->key_len,
                  impl->xcghash, impl->xcghash_len,
                  impl->session_id, impl->session_id_len,
                  impl->type, key, keylen);
}
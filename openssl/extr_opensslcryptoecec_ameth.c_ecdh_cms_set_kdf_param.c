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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_CTX_set_ecdh_cofactor_mode (int /*<<< orphan*/ *,int) ; 
 scalar_t__ EVP_PKEY_CTX_set_ecdh_kdf_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_PKEY_CTX_set_ecdh_kdf_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_ECDH_KDF_X9_63 ; 
 int /*<<< orphan*/ * EVP_get_digestbynid (int) ; 
 int NID_dh_cofactor_kdf ; 
 int NID_dh_std_kdf ; 
 int NID_undef ; 
 int /*<<< orphan*/  OBJ_find_sigid_algs (int,int*,int*) ; 

__attribute__((used)) static int ecdh_cms_set_kdf_param(EVP_PKEY_CTX *pctx, int eckdf_nid)
{
    int kdf_nid, kdfmd_nid, cofactor;
    const EVP_MD *kdf_md;
    if (eckdf_nid == NID_undef)
        return 0;

    /* Lookup KDF type, cofactor mode and digest */
    if (!OBJ_find_sigid_algs(eckdf_nid, &kdfmd_nid, &kdf_nid))
        return 0;

    if (kdf_nid == NID_dh_std_kdf)
        cofactor = 0;
    else if (kdf_nid == NID_dh_cofactor_kdf)
        cofactor = 1;
    else
        return 0;

    if (EVP_PKEY_CTX_set_ecdh_cofactor_mode(pctx, cofactor) <= 0)
        return 0;

    if (EVP_PKEY_CTX_set_ecdh_kdf_type(pctx, EVP_PKEY_ECDH_KDF_X9_63) <= 0)
        return 0;

    kdf_md = EVP_get_digestbynid(kdfmd_nid);
    if (!kdf_md)
        return 0;

    if (EVP_PKEY_CTX_set_ecdh_kdf_md(pctx, kdf_md) <= 0)
        return 0;
    return 1;
}
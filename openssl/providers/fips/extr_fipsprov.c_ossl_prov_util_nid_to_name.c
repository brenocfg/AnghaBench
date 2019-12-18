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

/* Variables and functions */
#define  NID_aes_128_cbc 163 
#define  NID_aes_128_ccm 162 
#define  NID_aes_128_ctr 161 
#define  NID_aes_128_ecb 160 
#define  NID_aes_128_gcm 159 
#define  NID_aes_128_xts 158 
#define  NID_aes_192_cbc 157 
#define  NID_aes_192_ccm 156 
#define  NID_aes_192_ctr 155 
#define  NID_aes_192_ecb 154 
#define  NID_aes_192_gcm 153 
#define  NID_aes_256_cbc 152 
#define  NID_aes_256_ccm 151 
#define  NID_aes_256_ctr 150 
#define  NID_aes_256_ecb 149 
#define  NID_aes_256_gcm 148 
#define  NID_aes_256_xts 147 
#define  NID_des_ede3_cbc 146 
#define  NID_des_ede3_ecb 145 
#define  NID_id_aes128_wrap 144 
#define  NID_id_aes128_wrap_pad 143 
#define  NID_id_aes192_wrap 142 
#define  NID_id_aes192_wrap_pad 141 
#define  NID_id_aes256_wrap 140 
#define  NID_id_aes256_wrap_pad 139 
#define  NID_sha1 138 
#define  NID_sha224 137 
#define  NID_sha256 136 
#define  NID_sha384 135 
#define  NID_sha3_224 134 
#define  NID_sha3_256 133 
#define  NID_sha3_384 132 
#define  NID_sha3_512 131 
#define  NID_sha512 130 
#define  NID_sha512_224 129 
#define  NID_sha512_256 128 

const char *ossl_prov_util_nid_to_name(int nid)
{
    /* We don't have OBJ_nid2n() in FIPS_MODE so we have an explicit list */

    switch (nid) {
    /* Digests */
    case NID_sha1:
        return "SHA1";
    case NID_sha224:
        return "SHA-224";
    case NID_sha256:
        return "SHA-256";
    case NID_sha384:
        return "SHA-384";
    case NID_sha512:
        return "SHA-512";
    case NID_sha512_224:
        return "SHA-512/224";
    case NID_sha512_256:
        return "SHA-512/256";
    case NID_sha3_224:
        return "SHA3-224";
    case NID_sha3_256:
        return "SHA3-256";
    case NID_sha3_384:
        return "SHA3-384";
    case NID_sha3_512:
        return "SHA3-512";

    /* Ciphers */
    case NID_aes_256_ecb:
        return "AES-256-ECB";
    case NID_aes_192_ecb:
        return "AES-192-ECB";
    case NID_aes_128_ecb:
        return "AES-128-ECB";
    case NID_aes_256_cbc:
        return "AES-256-CBC";
    case NID_aes_192_cbc:
        return "AES-192-CBC";
    case NID_aes_128_cbc:
        return "AES-128-CBC";
    case NID_aes_256_ctr:
        return "AES-256-CTR";
    case NID_aes_192_ctr:
        return "AES-192-CTR";
    case NID_aes_128_ctr:
        return "AES-128-CTR";
    case NID_aes_256_xts:
        return "AES-256-XTS";
    case NID_aes_128_xts:
        return "AES-128-XTS";
    case NID_aes_256_gcm:
        return "AES-256-GCM";
    case NID_aes_192_gcm:
        return "AES-192-GCM";
    case NID_aes_128_gcm:
        return "AES-128-GCM";
    case NID_aes_256_ccm:
        return "AES-256-CCM";
    case NID_aes_192_ccm:
        return "AES-192-CCM";
    case NID_aes_128_ccm:
        return "AES-128-CCM";
    case NID_id_aes256_wrap:
        return "AES-256-WRAP";
    case NID_id_aes192_wrap:
        return "AES-192-WRAP";
    case NID_id_aes128_wrap:
        return "AES-128-WRAP";
    case NID_id_aes256_wrap_pad:
        return "AES-256-WRAP-PAD";
    case NID_id_aes192_wrap_pad:
        return "AES-192-WRAP-PAD";
    case NID_id_aes128_wrap_pad:
        return "AES-128-WRAP-PAD";
    case NID_des_ede3_ecb:
        return "DES-EDE3";
    case NID_des_ede3_cbc:
        return "DES-EDE3-CBC";
    default:
        break;
    }

    return NULL;
}
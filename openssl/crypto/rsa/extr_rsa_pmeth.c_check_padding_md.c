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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int EVP_MD_type (int /*<<< orphan*/  const*) ; 
#define  NID_md2 142 
#define  NID_md4 141 
#define  NID_md5 140 
#define  NID_md5_sha1 139 
#define  NID_mdc2 138 
#define  NID_ripemd160 137 
#define  NID_sha1 136 
#define  NID_sha224 135 
#define  NID_sha256 134 
#define  NID_sha384 133 
#define  NID_sha3_224 132 
#define  NID_sha3_256 131 
#define  NID_sha3_384 130 
#define  NID_sha3_512 129 
#define  NID_sha512 128 
 int /*<<< orphan*/  RSA_F_CHECK_PADDING_MD ; 
 int RSA_NO_PADDING ; 
 int /*<<< orphan*/  RSA_R_INVALID_DIGEST ; 
 int /*<<< orphan*/  RSA_R_INVALID_PADDING_MODE ; 
 int /*<<< orphan*/  RSA_R_INVALID_X931_DIGEST ; 
 int RSA_X931_PADDING ; 
 int RSA_X931_hash_id (int) ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_padding_md(const EVP_MD *md, int padding)
{
    int mdnid;

    if (!md)
        return 1;

    mdnid = EVP_MD_type(md);

    if (padding == RSA_NO_PADDING) {
        RSAerr(RSA_F_CHECK_PADDING_MD, RSA_R_INVALID_PADDING_MODE);
        return 0;
    }

    if (padding == RSA_X931_PADDING) {
        if (RSA_X931_hash_id(mdnid) == -1) {
            RSAerr(RSA_F_CHECK_PADDING_MD, RSA_R_INVALID_X931_DIGEST);
            return 0;
        }
    } else {
        switch(mdnid) {
        /* List of all supported RSA digests */
        case NID_sha1:
        case NID_sha224:
        case NID_sha256:
        case NID_sha384:
        case NID_sha512:
        case NID_md5:
        case NID_md5_sha1:
        case NID_md2:
        case NID_md4:
        case NID_mdc2:
        case NID_ripemd160:
        case NID_sha3_224:
        case NID_sha3_256:
        case NID_sha3_384:
        case NID_sha3_512:
            return 1;

        default:
            RSAerr(RSA_F_CHECK_PADDING_MD, RSA_R_INVALID_DIGEST);
            return 0;

        }
    }

    return 1;
}
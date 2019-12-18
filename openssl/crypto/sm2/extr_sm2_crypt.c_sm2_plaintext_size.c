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
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/  const*) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SM2_F_SM2_PLAINTEXT_SIZE ; 
 int /*<<< orphan*/  SM2_R_INVALID_DIGEST ; 
 int /*<<< orphan*/  SM2_R_INVALID_ENCODING ; 
 int /*<<< orphan*/  SM2_R_INVALID_FIELD ; 
 int /*<<< orphan*/  SM2err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ec_field_size (int /*<<< orphan*/ ) ; 

int sm2_plaintext_size(const EC_KEY *key, const EVP_MD *digest, size_t msg_len,
                       size_t *pt_size)
{
    const size_t field_size = ec_field_size(EC_KEY_get0_group(key));
    const int md_size = EVP_MD_size(digest);
    size_t overhead;

    if (md_size < 0) {
        SM2err(SM2_F_SM2_PLAINTEXT_SIZE, SM2_R_INVALID_DIGEST);
        return 0;
    }
    if (field_size == 0) {
        SM2err(SM2_F_SM2_PLAINTEXT_SIZE, SM2_R_INVALID_FIELD);
        return 0;
    }

    overhead = 10 + 2 * field_size + (size_t)md_size;
    if (msg_len <= overhead) {
        SM2err(SM2_F_SM2_PLAINTEXT_SIZE, SM2_R_INVALID_ENCODING);
        return 0;
    }

    *pt_size = msg_len - overhead;
    return 1;
}
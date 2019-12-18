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
struct TYPE_3__ {int* encryption_key; int key_len; int* user_key; scalar_t__ mode; int* encrypt_id; } ;
typedef  int HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_MD5_CTX ;
typedef  TYPE_1__* HPDF_Encrypt ;
typedef  int HPDF_BYTE ;
typedef  int /*<<< orphan*/  HPDF_ARC4_Ctx_Rec ;

/* Variables and functions */
 int /*<<< orphan*/  ARC4CryptBuf (int /*<<< orphan*/ *,int*,int*,int) ; 
 int /*<<< orphan*/  ARC4Init (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ HPDF_ENCRYPT_R3 ; 
 int HPDF_ID_LEN ; 
 int /*<<< orphan*/  HPDF_MD5Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_MD5Update (int /*<<< orphan*/ *,int*,int) ; 
 int HPDF_MD5_KEY_LEN ; 
 int /*<<< orphan*/  HPDF_MemCpy (int*,int*,int) ; 
 int /*<<< orphan*/  HPDF_MemSet (int*,int /*<<< orphan*/ ,int) ; 
 int* HPDF_PADDING_STRING ; 
 int HPDF_PASSWD_LEN ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
HPDF_Encrypt_CreateUserKey  (HPDF_Encrypt  attr)
{
    HPDF_ARC4_Ctx_Rec ctx;

    HPDF_PTRACE((" HPDF_Encrypt_CreateUserKey\n"));

    /* Algorithm 3.4/5 step1 */

    /* Algorithm 3.4 step2 */
    ARC4Init(&ctx, attr->encryption_key, attr->key_len);
    ARC4CryptBuf(&ctx, HPDF_PADDING_STRING, attr->user_key, HPDF_PASSWD_LEN);

    if (attr->mode == HPDF_ENCRYPT_R3) {
        HPDF_MD5_CTX md5_ctx;
        HPDF_BYTE digest[HPDF_MD5_KEY_LEN];
        HPDF_BYTE digest2[HPDF_MD5_KEY_LEN];
        HPDF_UINT i;

        /* Algorithm 3.5 step2 (same as Algorithm3.2 step2) */
        HPDF_MD5Init(&md5_ctx);
        HPDF_MD5Update(&md5_ctx, HPDF_PADDING_STRING, HPDF_PASSWD_LEN);

        /* Algorithm 3.5 step3 */
        HPDF_MD5Update(&md5_ctx, attr->encrypt_id, HPDF_ID_LEN);
        HPDF_MD5Final(digest, &md5_ctx);

        HPDF_PTRACE(("@ Algorithm 3.5 step 3\n"));

        /* Algorithm 3.5 step4 */
        ARC4Init(&ctx, attr->encryption_key, attr->key_len);
        ARC4CryptBuf(&ctx, digest, digest2, HPDF_MD5_KEY_LEN);

        HPDF_PTRACE(("@ Algorithm 3.5 step 4\n"));

        /* Algorithm 3.5 step5 */
        for (i = 1; i <= 19; i++) {
            HPDF_UINT j;
            HPDF_BYTE new_key[HPDF_MD5_KEY_LEN];

            HPDF_PTRACE(("@ Algorithm 3.5 step 5 loop %u\n", i));

            for (j = 0; j < attr->key_len; j++)
                new_key[j] = (HPDF_BYTE)(attr->encryption_key[j] ^ i);

            HPDF_MemCpy (digest, digest2, HPDF_MD5_KEY_LEN);

            ARC4Init(&ctx, new_key, attr->key_len);
            ARC4CryptBuf(&ctx, digest, digest2, HPDF_MD5_KEY_LEN);
        }

        /* use the result of Algorithm 3.4 as 'arbitrary padding' */
        HPDF_MemSet (attr->user_key, 0, HPDF_PASSWD_LEN);
        HPDF_MemCpy (attr->user_key, digest2, HPDF_MD5_KEY_LEN);
    }
}
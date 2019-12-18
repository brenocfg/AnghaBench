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
struct TYPE_3__ {int* owner_passwd; scalar_t__ mode; int key_len; int* user_passwd; int* owner_key; } ;
typedef  int HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_MD5_CTX ;
typedef  TYPE_1__* HPDF_Encrypt ;
typedef  int HPDF_BYTE ;
typedef  int /*<<< orphan*/  HPDF_ARC4_Ctx_Rec ;

/* Variables and functions */
 int /*<<< orphan*/  ARC4CryptBuf (int /*<<< orphan*/ *,int*,int*,int) ; 
 int /*<<< orphan*/  ARC4Init (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ HPDF_ENCRYPT_R3 ; 
 int /*<<< orphan*/  HPDF_MD5Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_MD5Update (int /*<<< orphan*/ *,int*,int) ; 
 int HPDF_MD5_KEY_LEN ; 
 int /*<<< orphan*/  HPDF_MemCpy (int*,int*,int) ; 
 int HPDF_PASSWD_LEN ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
HPDF_Encrypt_CreateOwnerKey  (HPDF_Encrypt  attr)
{
    HPDF_ARC4_Ctx_Rec rc4_ctx;
    HPDF_MD5_CTX md5_ctx;
    HPDF_BYTE digest[HPDF_MD5_KEY_LEN];
    HPDF_BYTE tmppwd[HPDF_PASSWD_LEN];

    HPDF_PTRACE((" HPDF_Encrypt_CreateOwnerKey\n"));

    /* create md5-digest using the value of owner_passwd */

    /* Algorithm 3.3 step 2 */
    HPDF_MD5Init(&md5_ctx);
    HPDF_MD5Update(&md5_ctx, attr->owner_passwd, HPDF_PASSWD_LEN);

    HPDF_PTRACE(("@ Algorithm 3.3 step 2\n"));

    HPDF_MD5Final(digest, &md5_ctx);

    /* Algorithm 3.3 step 3 (Revision 3 only) */
    if (attr->mode == HPDF_ENCRYPT_R3) {
        HPDF_UINT i;

        for (i = 0; i < 50; i++) {
            HPDF_MD5Init(&md5_ctx);

            /* HPDF_MD5Update (&md5_ctx, digest, HPDF_MD5_KEY_LEN); */
            HPDF_MD5Update (&md5_ctx, digest, attr->key_len);
            HPDF_MD5Final(digest, &md5_ctx);

            HPDF_PTRACE(("@ Algorithm 3.3 step 3 loop %u\n", i));
        }
    }

    /* Algorithm 3.3 step 4 */
    HPDF_PTRACE(("@ Algorithm 3.3 step 7 loop 0\n"));

    ARC4Init (&rc4_ctx, digest, attr->key_len);

    HPDF_PTRACE(("@ Algorithm 3.3 step 5\n"));

    /* Algorithm 3.3 step 6 */
    HPDF_PTRACE(("@ Algorithm 3.3 step 6\n"));
    ARC4CryptBuf (&rc4_ctx, attr->user_passwd, tmppwd, HPDF_PASSWD_LEN);

    /* Algorithm 3.3 step 7 */
    HPDF_PTRACE(("@ Algorithm 3.3 step 7\n"));
    if (attr->mode == HPDF_ENCRYPT_R3) {
        HPDF_BYTE tmppwd2[HPDF_PASSWD_LEN];
        HPDF_UINT i;

        for (i = 1; i <= 19; i++) {
            HPDF_UINT j;
            HPDF_BYTE new_key[HPDF_MD5_KEY_LEN];

            for (j = 0; j < attr->key_len; j++)
                new_key[j] = (HPDF_BYTE)(digest[j] ^ i);

            HPDF_PTRACE(("@ Algorithm 3.3 step 7 loop %u\n", i));

            HPDF_MemCpy (tmppwd2, tmppwd, HPDF_PASSWD_LEN);
            ARC4Init(&rc4_ctx, new_key, attr->key_len);
            ARC4CryptBuf(&rc4_ctx, tmppwd2, tmppwd, HPDF_PASSWD_LEN);
        }
    }

    /* Algorithm 3.3 step 8 */
    HPDF_PTRACE(("@ Algorithm 3.3 step 8\n"));
    HPDF_MemCpy (attr->owner_key, tmppwd, HPDF_PASSWD_LEN);
}
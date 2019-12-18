#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  N; } ;
struct TYPE_4__ {TYPE_2__ rsa; int /*<<< orphan*/  aes; int /*<<< orphan*/  des; int /*<<< orphan*/  des3; int /*<<< orphan*/  rc2; } ;
typedef  TYPE_1__ KEY_CONTEXT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  const BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int ALG_ID ;

/* Variables and functions */
#define  CALG_3DES 138 
#define  CALG_3DES_112 137 
#define  CALG_AES 136 
#define  CALG_AES_128 135 
#define  CALG_AES_192 134 
#define  CALG_AES_256 133 
#define  CALG_DES 132 
#define  CALG_RC2 131 
#define  CALG_RSA_KEYX 130 
#define  CALG_RSA_SIGN 129 
#define  CALG_SSL3_SHAMD5 128 
 int /*<<< orphan*/  CRYPT_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  const* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  NTE_BAD_ALGID ; 
 int /*<<< orphan*/  NTE_FAIL ; 
 int /*<<< orphan*/  NTE_NO_MEMORY ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  aes_ecb_decrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_ecb_encrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  des3_ecb_decrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  des3_ecb_encrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  des_ecb_decrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  des_ecb_encrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned long) ; 
 int /*<<< orphan*/  mp_count_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc2_ecb_decrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc2_ecb_encrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reverse_bytes (int /*<<< orphan*/  const*,unsigned long) ; 
 int /*<<< orphan*/  rsa_exptmod (int /*<<< orphan*/  const*,unsigned long,int /*<<< orphan*/  const*,unsigned long*,int /*<<< orphan*/ ,TYPE_2__*) ; 

BOOL encrypt_block_impl(ALG_ID aiAlgid, DWORD dwKeySpec, KEY_CONTEXT *pKeyContext, const BYTE *in,
                        BYTE *out, DWORD enc)
{
    unsigned long inlen, outlen;
    BYTE *in_reversed = NULL;
        
    switch (aiAlgid) {
        case CALG_RC2:
            if (enc) {
                rc2_ecb_encrypt(in, out, &pKeyContext->rc2);
            } else {
                rc2_ecb_decrypt(in, out, &pKeyContext->rc2);
            }
            break;

        case CALG_3DES:
        case CALG_3DES_112:
            if (enc) {
                des3_ecb_encrypt(in, out, &pKeyContext->des3);
            } else {
                des3_ecb_decrypt(in, out, &pKeyContext->des3);
            }
            break;

        case CALG_DES:
            if (enc) {
                des_ecb_encrypt(in, out, &pKeyContext->des);
            } else {
                des_ecb_decrypt(in, out, &pKeyContext->des);
            }
            break;

        case CALG_AES:
        case CALG_AES_128:
        case CALG_AES_192:
        case CALG_AES_256:
            if (enc) {
                aes_ecb_encrypt(in, out, &pKeyContext->aes);
            } else {
                aes_ecb_decrypt(in, out, &pKeyContext->aes);
            }
            break;

        case CALG_RSA_KEYX:
        case CALG_RSA_SIGN:
        case CALG_SSL3_SHAMD5:
            outlen = inlen = (mp_count_bits(&pKeyContext->rsa.N)+7)/8;
            if (enc) {
                if (rsa_exptmod(in, inlen, out, &outlen, dwKeySpec, &pKeyContext->rsa) != CRYPT_OK) {
                    SetLastError(NTE_FAIL);
                    return FALSE;
                }
                reverse_bytes(out, outlen);
            } else {
                in_reversed = HeapAlloc(GetProcessHeap(), 0, inlen);
                if (!in_reversed) {
                    SetLastError(NTE_NO_MEMORY);
                    return FALSE;
                }
                memcpy(in_reversed, in, inlen);
                reverse_bytes(in_reversed, inlen);
                if (rsa_exptmod(in_reversed, inlen, out, &outlen, dwKeySpec, &pKeyContext->rsa) != CRYPT_OK) {
                    HeapFree(GetProcessHeap(), 0, in_reversed);
                    SetLastError(NTE_FAIL);
                    return FALSE;
                }
                HeapFree(GetProcessHeap(), 0, in_reversed);
            }
            break;

        default:
            SetLastError(NTE_BAD_ALGID);
            return FALSE;
    }

    return TRUE;
}
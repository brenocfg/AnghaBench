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
struct TYPE_3__ {size_t key_len; int /*<<< orphan*/  md5_encryption_key; int /*<<< orphan*/  arc4ctx; void** encryption_key; } ;
typedef  int HPDF_UINT32 ;
typedef  int HPDF_UINT16 ;
typedef  size_t HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_MD5_CTX ;
typedef  int /*<<< orphan*/  HPDF_INT ;
typedef  TYPE_1__* HPDF_Encrypt ;
typedef  void* HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ARC4Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t HPDF_ENCRYPT_KEY_MAX ; 
 int /*<<< orphan*/  HPDF_MD5Final (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_MD5Update (int /*<<< orphan*/ *,void**,size_t) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
HPDF_Encrypt_InitKey  (HPDF_Encrypt  attr,
                       HPDF_UINT32       object_id,
                       HPDF_UINT16       gen_no)
{
    HPDF_MD5_CTX ctx;
    HPDF_UINT key_len;

    HPDF_PTRACE((" HPDF_Encrypt_Init\n"));

    attr->encryption_key[attr->key_len] = (HPDF_BYTE)object_id;
    attr->encryption_key[attr->key_len + 1] = (HPDF_BYTE)(object_id >> 8);
    attr->encryption_key[attr->key_len + 2] = (HPDF_BYTE)(object_id >> 16);
    attr->encryption_key[attr->key_len + 3] = (HPDF_BYTE)gen_no;
    attr->encryption_key[attr->key_len + 4] = (HPDF_BYTE)(gen_no >> 8);

    HPDF_PTRACE(("@@@ OID=%u, gen_no=%u\n", (HPDF_INT)object_id, gen_no));

    HPDF_MD5Init(&ctx);
    HPDF_MD5Update(&ctx, attr->encryption_key, attr->key_len + 5);
    HPDF_MD5Final(attr->md5_encryption_key, &ctx);

    key_len = (attr->key_len + 5 > HPDF_ENCRYPT_KEY_MAX) ?
                    HPDF_ENCRYPT_KEY_MAX : attr->key_len + 5;

    ARC4Init(&attr->arc4ctx, attr->md5_encryption_key, key_len);
}
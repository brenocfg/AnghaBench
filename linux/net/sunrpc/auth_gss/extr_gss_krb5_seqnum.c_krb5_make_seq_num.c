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
typedef  int u32 ;
struct krb5_ctx {scalar_t__ enctype; } ;
struct crypto_sync_skcipher {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ ENCTYPE_ARCFOUR_HMAC ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_encrypt (struct crypto_sync_skcipher*,unsigned char*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  krb5_make_rc4_seq_num (struct krb5_ctx*,int,int,unsigned char*,unsigned char*) ; 

s32
krb5_make_seq_num(struct krb5_ctx *kctx,
		struct crypto_sync_skcipher *key,
		int direction,
		u32 seqnum,
		unsigned char *cksum, unsigned char *buf)
{
	unsigned char *plain;
	s32 code;

	if (kctx->enctype == ENCTYPE_ARCFOUR_HMAC)
		return krb5_make_rc4_seq_num(kctx, direction, seqnum,
					     cksum, buf);

	plain = kmalloc(8, GFP_NOFS);
	if (!plain)
		return -ENOMEM;

	plain[0] = (unsigned char) (seqnum & 0xff);
	plain[1] = (unsigned char) ((seqnum >> 8) & 0xff);
	plain[2] = (unsigned char) ((seqnum >> 16) & 0xff);
	plain[3] = (unsigned char) ((seqnum >> 24) & 0xff);

	plain[4] = direction;
	plain[5] = direction;
	plain[6] = direction;
	plain[7] = direction;

	code = krb5_encrypt(key, cksum, plain, buf, 8);
	kfree(plain);
	return code;
}
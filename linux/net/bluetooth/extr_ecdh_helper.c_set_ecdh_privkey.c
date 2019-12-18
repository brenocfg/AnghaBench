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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ecdh {int key_size; int /*<<< orphan*/ * key; int /*<<< orphan*/  curve_id; int /*<<< orphan*/  member_0; } ;
struct crypto_kpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECC_CURVE_NIST_P256 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int crypto_ecdh_encode_key (int /*<<< orphan*/ *,unsigned int,struct ecdh*) ; 
 unsigned int crypto_ecdh_key_len (struct ecdh*) ; 
 int crypto_kpp_set_secret (struct crypto_kpp*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_digits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int set_ecdh_privkey(struct crypto_kpp *tfm, const u8 private_key[32])
{
	u8 *buf, *tmp = NULL;
	unsigned int buf_len;
	int err;
	struct ecdh p = {0};

	p.curve_id = ECC_CURVE_NIST_P256;

	if (private_key) {
		tmp = kmalloc(32, GFP_KERNEL);
		if (!tmp)
			return -ENOMEM;
		swap_digits((u64 *)private_key, (u64 *)tmp, 4);
		p.key = tmp;
		p.key_size = 32;
	}

	buf_len = crypto_ecdh_key_len(&p);
	buf = kmalloc(buf_len, GFP_KERNEL);
	if (!buf) {
		err = -ENOMEM;
		goto free_tmp;
	}

	err = crypto_ecdh_encode_key(buf, buf_len, &p);
	if (err)
		goto free_all;

	err = crypto_kpp_set_secret(tfm, buf, buf_len);
	/* fall through */
free_all:
	kzfree(buf);
free_tmp:
	kzfree(tmp);
	return err;
}
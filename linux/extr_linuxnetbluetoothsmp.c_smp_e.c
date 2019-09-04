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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  const u8 ;
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SMP_DBG (char*,int /*<<< orphan*/  const*,...) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (struct crypto_cipher*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int crypto_cipher_setkey (struct crypto_cipher*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  swap_buf (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int smp_e(struct crypto_cipher *tfm, const u8 *k, u8 *r)
{
	uint8_t tmp[16], data[16];
	int err;

	SMP_DBG("k %16phN r %16phN", k, r);

	if (!tfm) {
		BT_ERR("tfm %p", tfm);
		return -EINVAL;
	}

	/* The most significant octet of key corresponds to k[0] */
	swap_buf(k, tmp, 16);

	err = crypto_cipher_setkey(tfm, tmp, 16);
	if (err) {
		BT_ERR("cipher setkey failed: %d", err);
		return err;
	}

	/* Most significant octet of plaintextData corresponds to data[0] */
	swap_buf(r, data, 16);

	crypto_cipher_encrypt_one(tfm, data, data);

	/* Most significant octet of encryptedData corresponds to data[0] */
	swap_buf(data, r, 16);

	SMP_DBG("r %16phN", r);

	return err;
}
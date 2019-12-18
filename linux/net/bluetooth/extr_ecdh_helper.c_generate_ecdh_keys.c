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
struct crypto_kpp {int dummy; } ;

/* Variables and functions */
 int generate_ecdh_public_key (struct crypto_kpp*,int /*<<< orphan*/ *) ; 
 int set_ecdh_privkey (struct crypto_kpp*,int /*<<< orphan*/ *) ; 

int generate_ecdh_keys(struct crypto_kpp *tfm, u8 public_key[64])
{
	int err;

	err = set_ecdh_privkey(tfm, NULL);
	if (err)
		return err;

	return generate_ecdh_public_key(tfm, public_key);
}
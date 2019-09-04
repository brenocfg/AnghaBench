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
typedef  int u32 ;
struct crypto_shash {int dummy; } ;
typedef  int /*<<< orphan*/  m ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_DBG (char*,int,...) ; 
 int aes_cmac (struct crypto_shash*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int smp_g2(struct crypto_shash *tfm_cmac, const u8 u[32], const u8 v[32],
		  const u8 x[16], const u8 y[16], u32 *val)
{
	u8 m[80], tmp[16];
	int err;

	SMP_DBG("u %32phN", u);
	SMP_DBG("v %32phN", v);
	SMP_DBG("x %16phN y %16phN", x, y);

	memcpy(m, y, 16);
	memcpy(m + 16, v, 32);
	memcpy(m + 48, u, 32);

	err = aes_cmac(tfm_cmac, x, m, sizeof(m), tmp);
	if (err)
		return err;

	*val = get_unaligned_le32(tmp);
	*val %= 1000000;

	SMP_DBG("val %06u", *val);

	return 0;
}
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
typedef  int /*<<< orphan*/  const u8 ;
struct crypto_shash {int dummy; } ;
typedef  int /*<<< orphan*/  m ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_DBG (char*,int /*<<< orphan*/  const*,...) ; 
 int aes_cmac (struct crypto_shash*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int smp_f6(struct crypto_shash *tfm_cmac, const u8 w[16],
		  const u8 n1[16], const u8 n2[16], const u8 r[16],
		  const u8 io_cap[3], const u8 a1[7], const u8 a2[7],
		  u8 res[16])
{
	u8 m[65];
	int err;

	SMP_DBG("w %16phN", w);
	SMP_DBG("n1 %16phN n2 %16phN", n1, n2);
	SMP_DBG("r %16phN io_cap %3phN a1 %7phN a2 %7phN", r, io_cap, a1, a2);

	memcpy(m, a2, 7);
	memcpy(m + 7, a1, 7);
	memcpy(m + 14, io_cap, 3);
	memcpy(m + 17, r, 16);
	memcpy(m + 33, n2, 16);
	memcpy(m + 49, n1, 16);

	err = aes_cmac(tfm_cmac, w, m, sizeof(m), res);
	if (err)
		return err;

	SMP_DBG("res %16phN", res);

	return err;
}
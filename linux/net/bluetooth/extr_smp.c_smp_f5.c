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
typedef  int u8 ;
struct crypto_shash {int dummy; } ;
typedef  int /*<<< orphan*/  m ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_DBG (char*,int const*,...) ; 
 int aes_cmac (struct crypto_shash*,int const*,int const*,int,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static int smp_f5(struct crypto_shash *tfm_cmac, const u8 w[32],
		  const u8 n1[16], const u8 n2[16], const u8 a1[7],
		  const u8 a2[7], u8 mackey[16], u8 ltk[16])
{
	/* The btle, salt and length "magic" values are as defined in
	 * the SMP section of the Bluetooth core specification. In ASCII
	 * the btle value ends up being 'btle'. The salt is just a
	 * random number whereas length is the value 256 in little
	 * endian format.
	 */
	const u8 btle[4] = { 0x65, 0x6c, 0x74, 0x62 };
	const u8 salt[16] = { 0xbe, 0x83, 0x60, 0x5a, 0xdb, 0x0b, 0x37, 0x60,
			      0x38, 0xa5, 0xf5, 0xaa, 0x91, 0x83, 0x88, 0x6c };
	const u8 length[2] = { 0x00, 0x01 };
	u8 m[53], t[16];
	int err;

	SMP_DBG("w %32phN", w);
	SMP_DBG("n1 %16phN n2 %16phN", n1, n2);
	SMP_DBG("a1 %7phN a2 %7phN", a1, a2);

	err = aes_cmac(tfm_cmac, salt, w, 32, t);
	if (err)
		return err;

	SMP_DBG("t %16phN", t);

	memcpy(m, length, 2);
	memcpy(m + 2, a2, 7);
	memcpy(m + 9, a1, 7);
	memcpy(m + 16, n2, 16);
	memcpy(m + 32, n1, 16);
	memcpy(m + 48, btle, 4);

	m[52] = 0; /* Counter */

	err = aes_cmac(tfm_cmac, t, m, sizeof(m), mackey);
	if (err)
		return err;

	SMP_DBG("mackey %16phN", mackey);

	m[52] = 1; /* Counter */

	err = aes_cmac(tfm_cmac, t, m, sizeof(m), ltk);
	if (err)
		return err;

	SMP_DBG("ltk %16phN", ltk);

	return 0;
}
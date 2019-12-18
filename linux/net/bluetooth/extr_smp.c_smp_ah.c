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

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int smp_e (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int smp_ah(const u8 irk[16], const u8 r[3], u8 res[3])
{
	u8 _res[16];
	int err;

	/* r' = padding || r */
	memcpy(_res, r, 3);
	memset(_res + 3, 0, 13);

	err = smp_e(irk, _res);
	if (err) {
		BT_ERR("Encrypt error");
		return err;
	}

	/* The output of the random address function ah is:
	 *	ah(k, r) = e(k, r') mod 2^24
	 * The output of the security function e is then truncated to 24 bits
	 * by taking the least significant 24 bits of the output of e as the
	 * result of ah.
	 */
	memcpy(res, _res, 3);

	return 0;
}
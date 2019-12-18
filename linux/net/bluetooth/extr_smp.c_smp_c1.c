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
typedef  int /*<<< orphan*/  u128 ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  SMP_DBG (char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int smp_e (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smp_c1(const u8 k[16],
		  const u8 r[16], const u8 preq[7], const u8 pres[7], u8 _iat,
		  const bdaddr_t *ia, u8 _rat, const bdaddr_t *ra, u8 res[16])
{
	u8 p1[16], p2[16];
	int err;

	SMP_DBG("k %16phN r %16phN", k, r);
	SMP_DBG("iat %u ia %6phN rat %u ra %6phN", _iat, ia, _rat, ra);
	SMP_DBG("preq %7phN pres %7phN", preq, pres);

	memset(p1, 0, 16);

	/* p1 = pres || preq || _rat || _iat */
	p1[0] = _iat;
	p1[1] = _rat;
	memcpy(p1 + 2, preq, 7);
	memcpy(p1 + 9, pres, 7);

	SMP_DBG("p1 %16phN", p1);

	/* res = r XOR p1 */
	u128_xor((u128 *) res, (u128 *) r, (u128 *) p1);

	/* res = e(k, res) */
	err = smp_e(k, res);
	if (err) {
		BT_ERR("Encrypt data error");
		return err;
	}

	/* p2 = padding || ia || ra */
	memcpy(p2, ra, 6);
	memcpy(p2 + 6, ia, 6);
	memset(p2 + 12, 0, 4);

	SMP_DBG("p2 %16phN", p2);

	/* res = res XOR p2 */
	u128_xor((u128 *) res, (u128 *) res, (u128 *) p2);

	/* res = e(k, res) */
	err = smp_e(k, res);
	if (err)
		BT_ERR("Encrypt data error");

	return err;
}
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

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int smp_e (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smp_s1(const u8 k[16],
		  const u8 r1[16], const u8 r2[16], u8 _r[16])
{
	int err;

	/* Just least significant octets from r1 and r2 are considered */
	memcpy(_r, r2, 8);
	memcpy(_r + 8, r1, 8);

	err = smp_e(k, _r);
	if (err)
		BT_ERR("Encrypt data error");

	return err;
}
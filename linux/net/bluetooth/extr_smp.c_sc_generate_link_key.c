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
struct smp_chan {int /*<<< orphan*/ * link_key; int /*<<< orphan*/  tfm_cmac; int /*<<< orphan*/ * tk; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SMP_FLAG_CT2 ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 scalar_t__ smp_h6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ *) ; 
 scalar_t__ smp_h7 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sc_generate_link_key(struct smp_chan *smp)
{
	/* From core spec. Spells out in ASCII as 'lebr'. */
	const u8 lebr[4] = { 0x72, 0x62, 0x65, 0x6c };

	smp->link_key = kzalloc(16, GFP_KERNEL);
	if (!smp->link_key)
		return;

	if (test_bit(SMP_FLAG_CT2, &smp->flags)) {
		/* SALT = 0x00000000000000000000000000000000746D7031 */
		const u8 salt[16] = { 0x31, 0x70, 0x6d, 0x74 };

		if (smp_h7(smp->tfm_cmac, smp->tk, salt, smp->link_key)) {
			kzfree(smp->link_key);
			smp->link_key = NULL;
			return;
		}
	} else {
		/* From core spec. Spells out in ASCII as 'tmp1'. */
		const u8 tmp1[4] = { 0x31, 0x70, 0x6d, 0x74 };

		if (smp_h6(smp->tfm_cmac, smp->tk, tmp1, smp->link_key)) {
			kzfree(smp->link_key);
			smp->link_key = NULL;
			return;
		}
	}

	if (smp_h6(smp->tfm_cmac, smp->link_key, lebr, smp->link_key)) {
		kzfree(smp->link_key);
		smp->link_key = NULL;
		return;
	}
}
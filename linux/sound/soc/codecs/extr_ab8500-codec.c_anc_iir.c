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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_ANCCONF1 ; 
 int /*<<< orphan*/  AB8500_ANCCONF1_ANCIIRINIT ; 
 int /*<<< orphan*/  AB8500_ANCCONF1_ANCIIRUPDATE ; 
 int /*<<< orphan*/  AB8500_ANCCONF7 ; 
 int /*<<< orphan*/  AB8500_ANCCONF8 ; 
 int AB8500_ANC_IIR_COEFFS ; 
 int AB8500_ANC_SM_DELAY ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void anc_iir(struct snd_soc_component *component, unsigned int bnk,
		unsigned int par, unsigned int val)
{
	if (par == 0) {
		if (bnk == 0) {
			snd_soc_component_update_bits(component, AB8500_ANCCONF1,
					BIT(AB8500_ANCCONF1_ANCIIRINIT),
					BIT(AB8500_ANCCONF1_ANCIIRINIT));
			usleep_range(AB8500_ANC_SM_DELAY, AB8500_ANC_SM_DELAY*2);
			snd_soc_component_update_bits(component, AB8500_ANCCONF1,
					BIT(AB8500_ANCCONF1_ANCIIRINIT), 0);
			usleep_range(AB8500_ANC_SM_DELAY, AB8500_ANC_SM_DELAY*2);
		} else {
			snd_soc_component_update_bits(component, AB8500_ANCCONF1,
					BIT(AB8500_ANCCONF1_ANCIIRUPDATE),
					BIT(AB8500_ANCCONF1_ANCIIRUPDATE));
		}
	} else if (par > 3) {
		snd_soc_component_write(component, AB8500_ANCCONF7, 0);
		snd_soc_component_write(component, AB8500_ANCCONF8, val >> 16 & 0xff);
	}

	snd_soc_component_write(component, AB8500_ANCCONF7, val >> 8 & 0xff);
	snd_soc_component_write(component, AB8500_ANCCONF8, val & 0xff);

	if (par == AB8500_ANC_IIR_COEFFS - 1 && bnk == 1)
		snd_soc_component_update_bits(component, AB8500_ANCCONF1,
			BIT(AB8500_ANCCONF1_ANCIIRUPDATE), 0);
}
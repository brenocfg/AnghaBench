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
typedef  int /*<<< orphan*/  u16 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M98088_BYTE0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M98088_BYTE1 (int /*<<< orphan*/ ) ; 
 int M98088_COEFS_PER_BAND ; 
 unsigned int M98088_REG_52_DAI1_EQ_BASE ; 
 unsigned int M98088_REG_84_DAI2_EQ_BASE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m98088_eq_band(struct snd_soc_component *component, unsigned int dai,
                   unsigned int band, u16 *coefs)
{
       unsigned int eq_reg;
       unsigned int i;

	if (WARN_ON(band > 4) ||
	    WARN_ON(dai > 1))
		return;

       /* Load the base register address */
       eq_reg = dai ? M98088_REG_84_DAI2_EQ_BASE : M98088_REG_52_DAI1_EQ_BASE;

       /* Add the band address offset, note adjustment for word address */
       eq_reg += band * (M98088_COEFS_PER_BAND << 1);

       /* Step through the registers and coefs */
       for (i = 0; i < M98088_COEFS_PER_BAND; i++) {
               snd_soc_component_write(component, eq_reg++, M98088_BYTE1(coefs[i]));
               snd_soc_component_write(component, eq_reg++, M98088_BYTE0(coefs[i]));
       }
}
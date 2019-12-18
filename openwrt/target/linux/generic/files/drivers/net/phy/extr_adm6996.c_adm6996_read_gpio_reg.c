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
typedef  int u16 ;
struct adm6996_priv {int /*<<< orphan*/  eesk; int /*<<< orphan*/  eecs; int /*<<< orphan*/  eedi; } ;
typedef  enum admreg { ____Placeholder_admreg } admreg ;

/* Variables and functions */
 int /*<<< orphan*/  adm6996_gpio_adclk (struct adm6996_priv*,int) ; 
 int /*<<< orphan*/  adm6996_gpio_read (struct adm6996_priv*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  adm6996_gpio_write (struct adm6996_priv*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16
adm6996_read_gpio_reg(struct adm6996_priv *priv, enum admreg reg)
{
	/* cmd: 01 10 T DD R RRRRRR */
	u8 bits[6] = {
		0xFF, 0xFF, 0xFF, 0xFF,
		(0x06 << 4) | ((0 & 0x01) << 3 | (reg&64)>>6),
		((reg&63)<<2)
	};

	u8 rbits[4];

	/* Enable GPIO outputs with all pins to 0 */
	gpio_direction_output(priv->eecs, 0);
	gpio_direction_output(priv->eesk, 0);
	gpio_direction_output(priv->eedi, 0);

	adm6996_gpio_write(priv, 0, bits, 46);
	gpio_direction_input(priv->eedi);
	adm6996_gpio_adclk(priv, 2);
	adm6996_gpio_read(priv, 0, rbits, 32);

	/* Extra clock(s) required per datasheet */
	adm6996_gpio_adclk(priv, 2);

	/* Disable GPIO outputs */
	gpio_direction_input(priv->eecs);
	gpio_direction_input(priv->eesk);

	 /* EEPROM has 16-bit registers, but pumps out two registers in one request */
	return (reg & 0x01 ?  (rbits[0]<<8) | rbits[1] : (rbits[2]<<8) | (rbits[3]));
}
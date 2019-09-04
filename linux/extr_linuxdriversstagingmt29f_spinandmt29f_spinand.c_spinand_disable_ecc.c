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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int OTP_ECC_MASK ; 
 int spinand_get_otp (struct spi_device*,int*) ; 
 int spinand_set_otp (struct spi_device*,int*) ; 

__attribute__((used)) static int spinand_disable_ecc(struct spi_device *spi_nand)
{
	int retval;
	u8 otp = 0;

	retval = spinand_get_otp(spi_nand, &otp);
	if (retval < 0)
		return retval;

	if ((otp & OTP_ECC_MASK) == OTP_ECC_MASK) {
		otp &= ~OTP_ECC_MASK;
		retval = spinand_set_otp(spi_nand, &otp);
		if (retval < 0)
			return retval;
		return spinand_get_otp(spi_nand, &otp);
	}
	return 0;
}
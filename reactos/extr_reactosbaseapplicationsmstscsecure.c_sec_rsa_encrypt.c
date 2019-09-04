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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  rdssl_mod_exp (char*,int,char*,int,char*,int,char*,int) ; 

__attribute__((used)) static void
sec_rsa_encrypt(uint8 * out, uint8 * in, int len, uint32 modulus_size, uint8 * modulus,
		uint8 * exponent)
{
	rdssl_mod_exp((char *)out, 64, (char *)in, 32, (char *)modulus, 64, (char *)exponent, 4);
}
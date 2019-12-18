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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crct10dif_fallback ; 
 int /*<<< orphan*/  crct10dif_tfm ; 
 int /*<<< orphan*/  crypto_shash_tfm (int /*<<< orphan*/ ) ; 
 char* crypto_tfm_alg_driver_name (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,...) ; 
 scalar_t__ static_key_false (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crc_t10dif_transform_show(char *buffer, const struct kernel_param *kp)
{
	if (static_key_false(&crct10dif_fallback))
		return sprintf(buffer, "fallback\n");

	return sprintf(buffer, "%s\n",
		crypto_tfm_alg_driver_name(crypto_shash_tfm(crct10dif_tfm)));
}
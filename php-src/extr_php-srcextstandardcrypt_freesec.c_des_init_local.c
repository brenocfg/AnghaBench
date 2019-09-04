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
struct php_crypt_extended_data {int initialized; scalar_t__ old_salt; scalar_t__ saltbits; scalar_t__ old_rawkey1; scalar_t__ old_rawkey0; } ;

/* Variables and functions */

__attribute__((used)) static void
des_init_local(struct php_crypt_extended_data *data)
{
	data->old_rawkey0 = data->old_rawkey1 = 0;
	data->saltbits = 0;
	data->old_salt = 0;

	data->initialized = 1;
}
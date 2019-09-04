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
 int omac1_aes_128_vector (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 

int omac1_aes_128(u8 *key, u8 *data, size_t data_len, u8 *mac)
{
	return omac1_aes_128_vector(key, 1, &data, &data_len, mac);
}
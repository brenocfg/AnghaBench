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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  x448_derive_public_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void X448_public_from_private(uint8_t out_public_value[56],
                              const uint8_t private_key[56])
{
    x448_derive_public_key(out_public_value, private_key);
}
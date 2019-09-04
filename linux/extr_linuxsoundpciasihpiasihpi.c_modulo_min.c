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

/* Variables and functions */

__attribute__((used)) static inline unsigned int modulo_min(unsigned int a, unsigned int b,
					unsigned long int modulus)
{
	unsigned int result;
	if (((a-b) % modulus) < (modulus/2))
		result = b;
	else
		result = a;

	return result;
}
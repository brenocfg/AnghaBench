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

__attribute__((used)) static int php_ifd_get16u(void *Short, int motorola_intel)
{
	if (motorola_intel) {
		return (((unsigned char *)Short)[0] << 8) | ((unsigned char *)Short)[1];
	} else {
		return (((unsigned char *)Short)[1] << 8) | ((unsigned char *)Short)[0];
	}
}
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

__attribute__((used)) static int _crypt_output_magic(const char *setting, char *output, int size)
{
	if (size < 3)
		return -1;

	output[0] = '*';
	output[1] = '0';
	output[2] = '\0';

	if (setting[0] == '*' && setting[1] == '0')
		output[1] = '1';

	return 0;
}
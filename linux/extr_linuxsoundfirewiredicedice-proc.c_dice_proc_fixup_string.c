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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32s (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dice_proc_fixup_string(char *s, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i += 4)
		cpu_to_le32s((u32 *)(s + i));

	for (i = 0; i < size - 2; ++i) {
		if (s[i] == '\0')
			return;
		if (s[i] == '\\' && s[i + 1] == '\\') {
			s[i + 2] = '\0';
			return;
		}
	}
	s[size - 1] = '\0';
}
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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
 int LEB_MAX_SIZE ; 

int dex_uleb128_len(const ut8 *ptr, int size) {
	int i = 1, result = *(ptr++);
	while (result > 0x7f && i <= LEB_MAX_SIZE && i < size) {
		result = *(ptr++);
		i++;
	}
	return i;
}
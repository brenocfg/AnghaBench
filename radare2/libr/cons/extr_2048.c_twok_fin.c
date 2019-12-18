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
 scalar_t__** twok_buf ; 

__attribute__((used)) static bool twok_fin() {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (!twok_buf[i][j]) {
				return true;
			}
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) {
			if (twok_buf[i][j] == twok_buf[i][j + 1]) {
				return true;
			}
		}
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++) {
			if (twok_buf[i][j] == twok_buf[i + 1][j]) {
				return true;
			}
		}
	}
	return false;
}
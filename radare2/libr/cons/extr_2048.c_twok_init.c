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
 scalar_t__ score ; 
 scalar_t__** twok_buf ; 

__attribute__((used)) static void twok_init() {
	int i, j;
	score = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			twok_buf[i][j] = 0;
		}
	}
}
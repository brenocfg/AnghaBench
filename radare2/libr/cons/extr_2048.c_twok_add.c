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
 int r_num_rand (int) ; 
 int** twok_buf ; 

__attribute__((used)) static void twok_add() {
	int i, j;
	while (true) {
		i = r_num_rand (4);
		j = r_num_rand (4);
		if (!twok_buf[i][j]) {
			twok_buf[i][j] = 1 + (r_num_rand (10) == 1);
			break;
		}
	}
}
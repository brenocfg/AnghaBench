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
 int /*<<< orphan*/  moves ; 
 int score ; 
 int /*<<< orphan*/  twok_add () ; 
 int** twok_buf ; 

__attribute__((used)) static void twok_move(int u, int v) {
	int i, j, k;
	int nKI = 0, nKJ = 0, nIK = 0, nJK = 0;
	int moved = 0;
	for (k = 0; k < 4; ++k) {
		for (i = 0; i < 4; ++i) {
			for (j = i + 1; j < 4 && !twok_buf[nKJ = u ? k : v ? j : 3 - j][nJK = !u ? k : v ? j : 3 - j]; ++j) {
				;
			}
			if (j == 4) {
				continue;
			}
			nKI = u? k: v? i: 3 - i;
			nIK = !u? k: v? i: 3 - i;
			if (!twok_buf[nKI][nIK]) {
				twok_buf[nKI][nIK] = twok_buf[nKJ][nJK];
				twok_buf[nKJ][nJK] = 0;
				--i;
				moved = 1;
			} else if (twok_buf[nKI][nIK] == twok_buf[nKJ][nJK]) {
				score += 1 << ++twok_buf[nKI][nIK];
				twok_buf[nKJ][nJK] = 0;
				moved = 1;
			}
		}
	}
	if (moved) {
		twok_add ();
		moves++;
	}
}
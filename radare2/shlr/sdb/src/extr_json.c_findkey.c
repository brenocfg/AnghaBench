#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int f; char* p; } ;
typedef  TYPE_1__ Rangstr ;

/* Variables and functions */

__attribute__((used)) static int findkey(Rangstr *rs) {
	int i;
	for (i = rs->f; i > 0; i--) {
		// Find the quote after the key
		if (rs->p[i] == '"') {
			for (--i; i > 0; i--) {
				// Find the quote before the key
				if (rs->p[i] == '"') {
					return i;
				}
			}
		}
	}
	return -1;
}
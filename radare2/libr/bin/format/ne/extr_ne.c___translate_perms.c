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
 int IS_DATA ; 
 int IS_RX ; 
 int R_PERM_R ; 
 int R_PERM_RWX ; 
 int R_PERM_X ; 

__attribute__((used)) static int __translate_perms(int flags) {
	int perms = 0;
	if (flags & IS_RX) {
		if (flags & IS_DATA) {
			perms = R_PERM_R;
		} else {
			perms = R_PERM_X;
		}
	}
	if (!perms) {
		perms = R_PERM_RWX;
	}
	return perms;
}
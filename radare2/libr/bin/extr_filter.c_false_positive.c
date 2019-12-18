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
typedef  size_t ut8 ;

/* Variables and functions */
 scalar_t__ IS_DIGIT (char const) ; 

__attribute__((used)) static bool false_positive(const char *str) {
	int i;
	ut8 bo[0x100];
	int up = 0;
	int lo = 0;
	int ot = 0;
	int di = 0;
	int ln = 0;
	int sp = 0;
	int nm = 0;
	for (i = 0; i < 0x100; i++) {
		bo[i] = 0;
	}
	for (i = 0; str[i]; i++) {
		if (IS_DIGIT (str[i])) {
			nm++;
		} else if (str[i]>='a' && str[i]<='z') {
			lo++;
		} else if (str[i]>='A' && str[i]<='Z') {
			up++;
		} else {
			ot++;
		}
		if (str[i]=='\\') {
			ot++;
		}
		if (str[i]==' ') {
			sp++;
		}
		bo[(ut8)str[i]] = 1;
		ln++;
	}
	for (i = 0; i<0x100; i++) {
		if (bo[i]) {
			di++;
		}
	}
	if (ln > 2 && str[0] != '_') {
		if (ln < 10) {
			return true;
		}
		if (ot >= (nm + up + lo)) {
			return true;
		}
		if (lo < 3) {
			return true;
		}
	}
	return false;
}
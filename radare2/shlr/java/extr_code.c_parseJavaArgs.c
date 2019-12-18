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
typedef  int /*<<< orphan*/  ut64 ;

/* Variables and functions */
 int /*<<< orphan*/  r_num_math (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int parseJavaArgs(char *str, ut64 *args, int args_sz) {
	int i, nargs = -1;
	char *q, *p = strchr (str, ' ');
	if (p) {
		*p++ = 0;
		nargs ++;
		for (i = 0; i < args_sz; i++) {
			nargs ++;
			q = strchr (p, ' ');
			if (q) {
				*q++ = 0;
			}
			args[i] = r_num_math (NULL, p);
			if (q) {
				p = q;
			} else {
				break;
			}
		}
	}
	return nargs;
}
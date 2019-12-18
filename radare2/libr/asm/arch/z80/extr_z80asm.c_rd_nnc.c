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
 int indx (char const**,char const**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readbyte ; 

__attribute__((used)) static int rd_nnc(const char **p) {
#define C 1
	int i;
	const char *list[] = {
		"( c )", "(*)", "a , (*)", NULL
	};
	i = indx (p, list, 1, &readbyte);
	if (i < 2) {
		return i;
	}
	return 2;
}
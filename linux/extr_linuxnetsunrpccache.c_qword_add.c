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
 int /*<<< orphan*/  ESCAPE_OCTAL ; 
 int string_escape_str (char*,char*,int,int /*<<< orphan*/ ,char*) ; 

void qword_add(char **bpp, int *lp, char *str)
{
	char *bp = *bpp;
	int len = *lp;
	int ret;

	if (len < 0) return;

	ret = string_escape_str(str, bp, len, ESCAPE_OCTAL, "\\ \n\t");
	if (ret >= len) {
		bp += len;
		len = -1;
	} else {
		bp += ret;
		len -= ret;
		*bp++ = ' ';
		len--;
	}
	*bpp = bp;
	*lp = len;
}
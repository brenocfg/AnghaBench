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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  PUTC (char) ; 
 int getc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_iptc_get1(FILE *fp, int spool, unsigned char **spoolbuf)
{
	int c;
	char cc;

	c = getc(fp);

	if (c == EOF) return EOF;

	if (spool > 0) {
		cc = c;
		PUTC(cc);
	}

	if (spoolbuf) *(*spoolbuf)++ = c;

	return c;
}
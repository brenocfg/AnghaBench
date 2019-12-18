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
typedef  int iconv_t ;

/* Variables and functions */
 int find_charmap (char const*) ; 
 unsigned int find_charset (char const*) ; 

iconv_t iconv_open(const char *to, const char *from)
{
	unsigned f, t;
	int m;

	if ((t = find_charset(to)) > 8)
		return -1;

	if ((f = find_charset(from)) < 255)
		return 0 | (t<<1) | (f<<8);

	if ((m = find_charmap(from)) > -1)
		return 1 | (t<<1) | (m<<8);

	return -1;
}
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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int utf32_to_utf8 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int uni2char(wchar_t uni, unsigned char *out, int boundlen)
{
	int n;

	if (boundlen <= 0)
		return -ENAMETOOLONG;

	n = utf32_to_utf8(uni, out, boundlen);
	if (n < 0) {
		*out = '?';
		return -EINVAL;
	}
	return n;
}
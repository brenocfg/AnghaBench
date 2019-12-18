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
 int ucs_wcwidth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf8_to_unicode (unsigned char const*) ; 

__attribute__((used)) static int
pg_utf_dsplen(const unsigned char *s)
{
	return ucs_wcwidth(utf8_to_unicode(s));
}
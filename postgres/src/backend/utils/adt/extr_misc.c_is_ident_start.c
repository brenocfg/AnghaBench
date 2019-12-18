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
 scalar_t__ IS_HIGHBIT_SET (unsigned char) ; 

__attribute__((used)) static bool
is_ident_start(unsigned char c)
{
	/* Underscores and ASCII letters are OK */
	if (c == '_')
		return true;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return true;
	/* Any high-bit-set character is OK (might be part of a multibyte char) */
	if (IS_HIGHBIT_SET(c))
		return true;
	return false;
}
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
 int is_ident_start (unsigned char) ; 

__attribute__((used)) static bool
is_ident_cont(unsigned char c)
{
	/* Can be digit or dollar sign ... */
	if ((c >= '0' && c <= '9') || c == '$')
		return true;
	/* ... or an identifier start character */
	return is_ident_start(c);
}
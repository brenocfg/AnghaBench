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
 int /*<<< orphan*/  isalnum (char) ; 
 int /*<<< orphan*/  isalpha (char) ; 

__attribute__((used)) static bool __btf_name_char_ok(char c, bool first, bool dot_ok)
{
	if ((first ? !isalpha(c) :
		     !isalnum(c)) &&
	    c != '_' &&
	    ((c == '.' && !dot_ok) ||
	      c != '.'))
		return false;
	return true;
}
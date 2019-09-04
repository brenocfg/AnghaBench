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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int win32_getattrs (int /*<<< orphan*/ *) ; 

int
mch_writable(char_u *name)
{
    int attrs = win32_getattrs(name);

    return (attrs != -1 && (!(attrs & FILE_ATTRIBUTE_READONLY)
			  || (attrs & FILE_ATTRIBUTE_DIRECTORY)));
}
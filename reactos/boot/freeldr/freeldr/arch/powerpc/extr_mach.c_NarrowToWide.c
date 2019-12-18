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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */

VOID NarrowToWide(WCHAR *wide_name, char *name)
{
    char *copy_name;
    WCHAR *wide_name_ptr;
    for (wide_name_ptr = wide_name, copy_name = name;
         (*wide_name_ptr = *copy_name);
         wide_name_ptr++, copy_name++);
}
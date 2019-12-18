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
 char* mp_imgfmt_to_name (int) ; 
 int strcmp (char*,char*) ; 

__attribute__((used)) static int cmp_imgfmt_name(const void *a, const void *b)
{
    char *name_a = mp_imgfmt_to_name(*(int *)a);
    char *name_b = mp_imgfmt_to_name(*(int *)b);

    return strcmp(name_a, name_b);
}
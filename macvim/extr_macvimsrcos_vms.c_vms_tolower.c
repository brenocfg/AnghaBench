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
 char TOLOWER_ASC (char) ; 
 int strlen (char*) ; 

char *
vms_tolower( char *name )
{
    int i,nlen = strlen(name);
    for (i = 0; i < nlen; i++)
	name[i] = TOLOWER_ASC(name[i]);
    return name;
}
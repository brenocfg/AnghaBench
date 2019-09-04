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
 int /*<<< orphan*/  WINE_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 int strcmp (void*,void const*) ; 
 int strlen (void*) ; 

__attribute__((used)) static int comp_FindSubFile(void *p, const void *key,
                            int leaf, void** next)
{
    *next = (char *)p+strlen(p)+(leaf?5:3);
    WINE_TRACE("Comparing %s with %s\n", debugstr_a((char *)p), debugstr_a((const char *)key));
    return strcmp(p, key);
}
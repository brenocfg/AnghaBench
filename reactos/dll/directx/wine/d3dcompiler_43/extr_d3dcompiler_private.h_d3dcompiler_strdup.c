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
typedef  scalar_t__ SIZE_T ;

/* Variables and functions */
 char* d3dcompiler_alloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static inline char *d3dcompiler_strdup(const char *string)
{
    char *copy;
    SIZE_T len;

    if (!string)
        return NULL;

    len = strlen(string);
    copy = d3dcompiler_alloc(len + 1);
    if (copy)
        memcpy(copy, string, len + 1);
    return copy;
}
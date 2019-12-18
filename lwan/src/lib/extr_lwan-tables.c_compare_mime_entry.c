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
 int strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int
compare_mime_entry(const void *a, const void *b)
{
    const char *exta = (const char *)a;
    const char *extb = (const char *)b;

    return strncmp(exta, extb, 8);
}
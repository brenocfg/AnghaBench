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
 char* talloc_strndup (void*,char const*,int) ; 

__attribute__((used)) static char *col_dup(void *talloc_ctx, const char *src)
{
    int length = 0;
    while (src[length] > 31)
        length++;

    return talloc_strndup(talloc_ctx, src, length);
}
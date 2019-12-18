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
struct bstr {int len; int /*<<< orphan*/ * start; } ;

/* Variables and functions */
 int /*<<< orphan*/  strchr (char const*,int /*<<< orphan*/ ) ; 

int bstrspn(struct bstr str, const char *accept)
{
    int i;
    for (i = 0; i < str.len; i++)
        if (!strchr(accept, str.start[i]))
            break;
    return i;
}
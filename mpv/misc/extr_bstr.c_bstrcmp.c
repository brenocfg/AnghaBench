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
struct bstr {scalar_t__ len; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPMIN (scalar_t__,scalar_t__) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bstrcmp(struct bstr str1, struct bstr str2)
{
    int ret = 0;
    if (str1.len && str2.len)
        ret = memcmp(str1.start, str2.start, MPMIN(str1.len, str2.len));

    if (!ret) {
        if (str1.len == str2.len)
            return 0;
        else if (str1.len > str2.len)
            return 1;
        else
            return -1;
    }
    return ret;
}
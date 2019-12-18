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
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  jsstr_as_rope (int /*<<< orphan*/ *) ; 
 int jsstr_cmp_str (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 unsigned int jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_try_flat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (unsigned int,unsigned int) ; 
 int ropes_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int jsstr_cmp(jsstr_t *str1, jsstr_t *str2)
{
    unsigned len1 = jsstr_length(str1);
    unsigned len2 = jsstr_length(str2);
    const WCHAR *str;
    int ret;

    str = jsstr_try_flat(str2);
    if(str) {
        ret = jsstr_cmp_str(str1, str, min(len1, len2));
        return ret || len1 == len2 ? ret : -1;
    }

    str = jsstr_try_flat(str1);
    if(str) {
        ret = jsstr_cmp_str(str2, str, min(len1, len2));
        return ret || len1 == len2 ? -ret : 1;
    }

    return ropes_cmp(jsstr_as_rope(str1), jsstr_as_rope(str2));
}
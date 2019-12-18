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
struct bstr {int /*<<< orphan*/  start; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int MPMIN (int /*<<< orphan*/ ,int) ; 
 struct bstr bstr_cut (struct bstr,int) ; 
 struct bstr bstr_lstrip (struct bstr) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 long long strtoll (char*,char**,int) ; 

long long bstrtoll(struct bstr str, struct bstr *rest, int base)
{
    str = bstr_lstrip(str);
    char buf[51];
    int len = MPMIN(str.len, 50);
    memcpy(buf, str.start, len);
    buf[len] = 0;
    char *endptr;
    long long r = strtoll(buf, &endptr, base);
    if (rest)
        *rest = bstr_cut(str, endptr - buf);
    return r;
}
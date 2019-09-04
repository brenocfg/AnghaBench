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
struct bstr {int len; } ;

/* Variables and functions */
 struct bstr bstr_cut (struct bstr,int) ; 
 struct bstr bstr_splice (struct bstr,int /*<<< orphan*/ ,int) ; 
 int bstrchr (struct bstr,char const) ; 

struct bstr bstr_splitchar(struct bstr str, struct bstr *rest, const char c)
{
    int pos = bstrchr(str, c);
    if (pos < 0)
        pos = str.len;
    if (rest)
        *rest = bstr_cut(str, pos + 1);
    return bstr_splice(str, 0, pos + 1);
}
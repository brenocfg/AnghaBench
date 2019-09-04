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
 struct bstr bstr_cut (struct bstr,int) ; 
 struct bstr bstr_splice (struct bstr,int /*<<< orphan*/ ,int) ; 
 int bstrcspn (struct bstr,char const*) ; 
 int /*<<< orphan*/  strchr (char const*,int /*<<< orphan*/ ) ; 

struct bstr bstr_split(struct bstr str, const char *sep, struct bstr *rest)
{
    int start;
    for (start = 0; start < str.len; start++)
        if (!strchr(sep, str.start[start]))
            break;
    str = bstr_cut(str, start);
    int end = bstrcspn(str, sep);
    if (rest) {
        *rest = bstr_cut(str, end);
    }
    return bstr_splice(str, 0, end);
}
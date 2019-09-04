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
struct bstr {char* start; int len; } ;

/* Variables and functions */
 struct bstr bstr_cut (struct bstr,int) ; 
 struct bstr bstr_splice (struct bstr,int /*<<< orphan*/ ,char*) ; 
 int bstrchr (struct bstr,char) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static struct bstr get_nextsep(struct bstr *ptr, char sep, bool modify)
{
    struct bstr str = *ptr;
    struct bstr orig = str;
    for (;;) {
        int idx = sep ? bstrchr(str, sep) : -1;
        if (idx > 0 && str.start[idx - 1] == '\\') {
            if (modify) {
                memmove(str.start + idx - 1, str.start + idx, str.len - idx);
                str.len--;
                str = bstr_cut(str, idx);
            } else
                str = bstr_cut(str, idx + 1);
        } else {
            str = bstr_cut(str, idx < 0 ? str.len : idx);
            break;
        }
    }
    *ptr = str;
    return bstr_splice(orig, 0, str.start - orig.start);
}
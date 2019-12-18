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
struct bstr {scalar_t__ len; scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ bstrcmp (struct bstr,struct bstr) ; 

__attribute__((used)) static inline bool bstr_equals(struct bstr str1, struct bstr str2)
{
    if (str1.len != str2.len)
        return false;

    return str1.start == str2.start || bstrcmp(str1, str2) == 0;
}
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
struct bstr {scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ bstr_endswith0 (struct bstr,char*) ; 
 struct bstr bstr_splice (struct bstr,int /*<<< orphan*/ ,scalar_t__) ; 

struct bstr bstr_strip_linebreaks(struct bstr str)
{
    if (bstr_endswith0(str, "\r\n")) {
        str = bstr_splice(str, 0, str.len - 2);
    } else if (bstr_endswith0(str, "\n")) {
        str = bstr_splice(str, 0, str.len - 1);
    }
    return str;
}
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
struct bstr {int dummy; } ;

/* Variables and functions */
 struct bstr bstr_cut (struct bstr,int) ; 
 struct bstr bstr_lstrip (struct bstr) ; 
 struct bstr bstr_splice (struct bstr,int /*<<< orphan*/ ,int) ; 
 int bstrchr (struct bstr,char) ; 
 char* bstrto0 (void*,struct bstr) ; 
 int /*<<< orphan*/  eat_char (struct bstr*,char) ; 

__attribute__((used)) static char *read_quoted(void *talloc_ctx, struct bstr *data)
{
    *data = bstr_lstrip(*data);
    if (!eat_char(data, '"'))
        return NULL;
    int end = bstrchr(*data, '"');
    if (end < 0)
        return NULL;
    struct bstr res = bstr_splice(*data, 0, end);
    *data = bstr_cut(*data, end + 1);
    return bstrto0(talloc_ctx, res);
}
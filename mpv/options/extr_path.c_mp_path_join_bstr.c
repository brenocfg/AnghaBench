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
struct bstr {int len; char* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (struct bstr) ; 
 char* bstrdup0 (void*,struct bstr) ; 
 char* talloc_asprintf (void*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

char *mp_path_join_bstr(void *talloc_ctx, struct bstr p1, struct bstr p2)
{
    bool test;
    if (p1.len == 0)
        return bstrdup0(talloc_ctx, p2);
    if (p2.len == 0)
        return bstrdup0(talloc_ctx, p1);

#if HAVE_DOS_PATHS
    test = (p2.len >= 2 && p2.start[1] == ':')
        || p2.start[0] == '\\' || p2.start[0] == '/';
#else
    test = p2.start[0] == '/';
#endif
    if (test)
        return bstrdup0(talloc_ctx, p2);   // absolute path

    bool have_separator;
    int endchar1 = p1.start[p1.len - 1];
#if HAVE_DOS_PATHS
    have_separator = endchar1 == '/' || endchar1 == '\\'
                     || (p1.len == 2 && endchar1 == ':'); // "X:" only
#else
    have_separator = endchar1 == '/';
#endif

    return talloc_asprintf(talloc_ctx, "%.*s%s%.*s", BSTR_P(p1),
                           have_separator ? "" : "/", BSTR_P(p2));
}
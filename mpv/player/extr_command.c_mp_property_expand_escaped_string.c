#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct MPContext {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  start; scalar_t__ len; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 TYPE_1__ bstr0 (char const*) ; 
 int /*<<< orphan*/  bstr_eatstart0 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  bstr_xappend (void*,TYPE_1__*,TYPE_1__) ; 
 int /*<<< orphan*/  mp_append_escaped_string (void*,TYPE_1__*,TYPE_1__*) ; 
 char* mp_property_expand_string (struct MPContext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 

char *mp_property_expand_escaped_string(struct MPContext *mpctx, const char *str)
{
    void *tmp = talloc_new(NULL);
    bstr strb = bstr0(str);
    bstr dst = {0};
    while (strb.len) {
        if (!mp_append_escaped_string(tmp, &dst, &strb)) {
            talloc_free(tmp);
            return talloc_strdup(NULL, "(broken escape sequences)");
        }
        // pass " through literally
        if (!bstr_eatstart0(&strb, "\""))
            break;
        bstr_xappend(tmp, &dst, bstr0("\""));
    }
    char *r = mp_property_expand_string(mpctx, dst.start);
    talloc_free(tmp);
    return r;
}
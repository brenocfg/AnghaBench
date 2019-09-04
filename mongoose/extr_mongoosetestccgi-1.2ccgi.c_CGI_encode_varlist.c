#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  value; struct TYPE_5__* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  varname; TYPE_2__* value; struct TYPE_4__* next; } ;
typedef  TYPE_1__ CGI_varlist ;
typedef  TYPE_2__ CGI_val ;

/* Variables and functions */
 char* mymalloc (int) ; 
 scalar_t__ urlcount (int /*<<< orphan*/ ,char const*) ; 
 char* urlencode (int /*<<< orphan*/ ,char*,char const*) ; 

char *
CGI_encode_varlist(CGI_varlist *vlist, const char *keep) {
    char *out, *p;
    CGI_varlist *v;
    CGI_val *value;
    int k = 0;

    /* calculate size of the output string */

    for (v = vlist; v != 0; v = v->next) {
        for (value = v->value; value != 0; value = value->next) {
            k += 2 + urlcount(v->varname, keep) +
                urlcount(value->value, keep);
        }
    }
    if (k == 0) {
        return 0;
    }
    p = out = mymalloc(k);

    /* URL encode each name=value pair */

    for (v = vlist; v != 0; v = v->next) {
        for (value = v->value; value != 0; value = value->next) {
            if (p != out) {
                *p++ = '&';
            }
            p = urlencode(v->varname, p, keep);
            *p++ = '=';
            p = urlencode(value->value, p, keep);
        }
    }
    *p = 0;
    return out;
}
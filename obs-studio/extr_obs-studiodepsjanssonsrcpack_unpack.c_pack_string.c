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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  scanner_t ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/ * json_null () ; 
 int /*<<< orphan*/ * json_stringn_nocheck (char*,size_t) ; 
 int /*<<< orphan*/ * jsonp_stringn_nocheck_own (char*,size_t) ; 
 int /*<<< orphan*/  next_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prev_token (int /*<<< orphan*/ *) ; 
 char* read_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,size_t*,int*) ; 
 char token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static json_t *pack_string(scanner_t *s, va_list *ap)
{
    char *str;
    size_t len;
    int ours;
    int nullable;

    next_token(s);
    nullable = token(s) == '?';
    if (!nullable)
        prev_token(s);

    str = read_string(s, ap, "string", &len, &ours);
    if (!str) {
        return nullable ? json_null() : NULL;
    } else if (ours) {
        return jsonp_stringn_nocheck_own(str, len);
    } else {
        return json_stringn_nocheck(str, len);
    }
}
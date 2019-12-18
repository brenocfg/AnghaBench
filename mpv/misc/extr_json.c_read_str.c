#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* string; } ;
struct mpv_node {TYPE_1__ u; int /*<<< orphan*/  format; } ;
struct TYPE_7__ {char* start; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_STRING ; 
 TYPE_2__ bstr0 (char*) ; 
 int /*<<< orphan*/  eat_c (char**,char) ; 
 int /*<<< orphan*/  mp_append_escaped_string (void*,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static int read_str(void *ta_parent, struct mpv_node *dst, char **src)
{
    if (!eat_c(src, '"'))
        return -1; // not a string
    char *str = *src;
    char *cur = str;
    bool has_escapes = false;
    while (cur[0] && cur[0] != '"') {
        if (cur[0] == '\\') {
            has_escapes = true;
            // skip >\"< and >\\< (latter to handle >\\"< correctly)
            if (cur[1] == '"' || cur[1] == '\\')
                cur++;
        }
        cur++;
    }
    if (cur[0] != '"')
        return -1; // invalid termination
    // Mutate input string so we have a null-terminated string to the literal.
    // This is a stupid micro-optimization, so we can avoid allocation.
    cur[0] = '\0';
    *src = cur + 1;
    if (has_escapes) {
        bstr unescaped = {0};
        bstr r = bstr0(str);
        if (!mp_append_escaped_string(ta_parent, &unescaped, &r))
            return -1; // broken escapes
        str = unescaped.start; // the function guarantees null-termination
    }
    dst->format = MPV_FORMAT_STRING;
    dst->u.string = str;
    return 0;
}
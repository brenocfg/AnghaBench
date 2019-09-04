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
typedef  char u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 scalar_t__ ngx_strstr (char*,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_play_parse_index(char type, u_char *args)
{
    u_char             *p, c;
    static u_char       name[] = "xindex=";

    name[0] = (u_char) type;

    for ( ;; ) {
        p = (u_char *) ngx_strstr(args, name);
        if (p == NULL) {
            return 0;
        }

        if (p != args) {
            c = *(p - 1);
            if (c != '?' && c != '&') {
                args = p + 1;
                continue;
            }
        }

        return atoi((char *) p + (sizeof(name) - 1));
    }
}
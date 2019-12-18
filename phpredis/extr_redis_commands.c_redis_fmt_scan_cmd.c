#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* c; int len; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ smart_string ;
typedef  size_t REDIS_SCAN_TYPE ;

/* Variables and functions */
 size_t TYPE_SCAN ; 
 int /*<<< orphan*/  redis_cmd_append_sstr (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  redis_cmd_append_sstr_long (TYPE_1__*,long) ; 
 int /*<<< orphan*/  redis_cmd_init_sstr (TYPE_1__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int redis_fmt_scan_cmd(char **cmd, REDIS_SCAN_TYPE type, char *key, int key_len,
                       long it, char *pat, int pat_len, long count)
{
    static char *kw[] = {"SCAN","SSCAN","HSCAN","ZSCAN"};
    int argc;
    smart_string cmdstr = {0};

    // Figure out our argument count
    argc = 1 + (type!=TYPE_SCAN) + (pat_len>0?2:0) + (count>0?2:0);

    redis_cmd_init_sstr(&cmdstr, argc, kw[type], strlen(kw[type]));

    // Append our key if it's not a regular SCAN command
    if (type != TYPE_SCAN) {
        redis_cmd_append_sstr(&cmdstr, key, key_len);
    }

    // Append cursor
    redis_cmd_append_sstr_long(&cmdstr, it);

    // Append count if we've got one
    if (count) {
        redis_cmd_append_sstr(&cmdstr,"COUNT",sizeof("COUNT")-1);
        redis_cmd_append_sstr_long(&cmdstr, count);
    }

    // Append pattern if we've got one
    if (pat_len) {
        redis_cmd_append_sstr(&cmdstr,"MATCH",sizeof("MATCH")-1);
        redis_cmd_append_sstr(&cmdstr,pat,pat_len);
    }

    // Push command to the caller, return length
    *cmd = cmdstr.c;
    return cmdstr.len;
}
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
typedef  scalar_t__ zend_ulong ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  smart_string ;
typedef  int /*<<< orphan*/  kbuf ;

/* Variables and functions */
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int redis_cmd_append_sstr (int /*<<< orphan*/ *,char*,int) ; 
 int snprintf (char*,int,char*,long) ; 

int redis_cmd_append_sstr_arrkey(smart_string *cmd, zend_string *kstr, zend_ulong idx)
{
    char *arg, kbuf[128];
    int len;

    if (kstr) {
        len = ZSTR_LEN(kstr);
        arg = ZSTR_VAL(kstr);
    } else {
        len = snprintf(kbuf, sizeof(kbuf), "%ld", (long)idx);
        arg = (char*)kbuf;
    }

    return redis_cmd_append_sstr(cmd, arg, len);
}
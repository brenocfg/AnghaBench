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
typedef  int /*<<< orphan*/  vstr_t ;
typedef  char unichar ;

/* Variables and functions */
 char* vstr_ins_blank_bytes (int /*<<< orphan*/ *,size_t,int) ; 

void vstr_ins_char(vstr_t *vstr, size_t char_pos, unichar chr) {
    // TODO UNICODE
    char *s = vstr_ins_blank_bytes(vstr, char_pos, 1);
    *s = chr;
}
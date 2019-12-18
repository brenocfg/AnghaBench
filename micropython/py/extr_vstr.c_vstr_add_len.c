#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* buf; int len; } ;
typedef  TYPE_1__ vstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  vstr_ensure_extra (TYPE_1__*,size_t) ; 

char *vstr_add_len(vstr_t *vstr, size_t len) {
    vstr_ensure_extra(vstr, len);
    char *buf = vstr->buf + vstr->len;
    vstr->len += len;
    return buf;
}
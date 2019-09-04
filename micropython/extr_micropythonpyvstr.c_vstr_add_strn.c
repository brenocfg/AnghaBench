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
struct TYPE_4__ {scalar_t__ len; scalar_t__ buf; } ;
typedef  TYPE_1__ vstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__,char const*,size_t) ; 
 int /*<<< orphan*/  vstr_ensure_extra (TYPE_1__*,size_t) ; 

void vstr_add_strn(vstr_t *vstr, const char *str, size_t len) {
    vstr_ensure_extra(vstr, len);
    memmove(vstr->buf + vstr->len, str, len);
    vstr->len += len;
}
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

/* Variables and functions */
 int /*<<< orphan*/  vstr_ensure_extra (int /*<<< orphan*/ *,size_t) ; 

void vstr_hint_size(vstr_t *vstr, size_t size) {
    vstr_ensure_extra(vstr, size);
}
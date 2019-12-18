#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct arl_callback_ptr {int /*<<< orphan*/  line; int /*<<< orphan*/  ff; TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  status_vmrss; } ;

/* Variables and functions */
 int /*<<< orphan*/  procfile_lineword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int procfile_linewords (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str2kernel_uint_t (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void arl_callback_status_vmrss(const char *name, uint32_t hash, const char *value, void *dst) {
    (void)name; (void)hash; (void)value;
    struct arl_callback_ptr *aptr = (struct arl_callback_ptr *)dst;
    if(unlikely(procfile_linewords(aptr->ff, aptr->line) < 3)) return;

    aptr->p->status_vmrss = str2kernel_uint_t(procfile_lineword(aptr->ff, aptr->line, 1));
}
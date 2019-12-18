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
typedef  int __u32 ;
struct TYPE_2__ {int nt_errcode; int /*<<< orphan*/ * nt_errstr; } ;

/* Variables and functions */
 TYPE_1__* nt_errs ; 
 int /*<<< orphan*/  pr_notice (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cifs_print_status(__u32 status_code)
{
	int idx = 0;

	while (nt_errs[idx].nt_errstr != NULL) {
		if (((nt_errs[idx].nt_errcode) & 0xFFFFFF) ==
		    (status_code & 0xFFFFFF)) {
			pr_notice("Status code returned 0x%08x %s\n",
				  status_code, nt_errs[idx].nt_errstr);
		}
		idx++;
	}
	return;
}
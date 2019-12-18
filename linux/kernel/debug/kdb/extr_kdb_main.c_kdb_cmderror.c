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
struct TYPE_2__ {int km_diag; int /*<<< orphan*/  km_msg; } ;

/* Variables and functions */
 int __nkdb_err ; 
 int /*<<< orphan*/  kdb_printf (char*,int,...) ; 
 TYPE_1__* kdbmsgs ; 

__attribute__((used)) static void kdb_cmderror(int diag)
{
	int i;

	if (diag >= 0) {
		kdb_printf("no error detected (diagnostic is %d)\n", diag);
		return;
	}

	for (i = 0; i < __nkdb_err; i++) {
		if (kdbmsgs[i].km_diag == diag) {
			kdb_printf("diag: %d: %s\n", diag, kdbmsgs[i].km_msg);
			return;
		}
	}

	kdb_printf("Unknown diag %d\n", -diag);
}
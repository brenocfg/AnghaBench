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
typedef  int /*<<< orphan*/  __u8 ;
typedef  scalar_t__ __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {scalar_t__ ntstatus; int /*<<< orphan*/  dos_code; int /*<<< orphan*/  dos_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRHRD ; 
 int /*<<< orphan*/  ERRgeneral ; 
 TYPE_1__* ntstatus_to_dos_map ; 

__attribute__((used)) static void
ntstatus_to_dos(__u32 ntstatus, __u8 *eclass, __u16 *ecode)
{
	int i;
	if (ntstatus == 0) {
		*eclass = 0;
		*ecode = 0;
		return;
	}
	for (i = 0; ntstatus_to_dos_map[i].ntstatus; i++) {
		if (ntstatus == ntstatus_to_dos_map[i].ntstatus) {
			*eclass = ntstatus_to_dos_map[i].dos_class;
			*ecode = ntstatus_to_dos_map[i].dos_code;
			return;
		}
	}
	*eclass = ERRHRD;
	*ecode = ERRgeneral;
}
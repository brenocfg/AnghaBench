#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_3__ {int /*<<< orphan*/  SASAddress; } ;
typedef  TYPE_1__ Mpi2BootDeviceSasWwid_t ;

/* Variables and functions */
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
_scsih_srch_boot_sas_address(u64 sas_address,
	Mpi2BootDeviceSasWwid_t *boot_device)
{
	return (sas_address == le64_to_cpu(boot_device->SASAddress)) ?  1 : 0;
}
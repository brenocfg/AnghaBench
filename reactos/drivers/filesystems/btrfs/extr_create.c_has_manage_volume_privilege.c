#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  SubjectSecurityContext; } ;
struct TYPE_7__ {int PrivilegeCount; TYPE_1__* Privilege; int /*<<< orphan*/  Control; } ;
struct TYPE_6__ {scalar_t__ Attributes; int /*<<< orphan*/  Luid; } ;
typedef  TYPE_2__ PRIVILEGE_SET ;
typedef  int /*<<< orphan*/  KPROCESSOR_MODE ;
typedef  TYPE_3__ ACCESS_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  PRIVILEGE_SET_ALL_NECESSARY ; 
 int /*<<< orphan*/  RtlConvertLongToLuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SE_MANAGE_VOLUME_PRIVILEGE ; 
 scalar_t__ SePrivilegeCheck (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool has_manage_volume_privilege(ACCESS_STATE* access_state, KPROCESSOR_MODE processor_mode) {
    PRIVILEGE_SET privset;

    privset.PrivilegeCount = 1;
    privset.Control = PRIVILEGE_SET_ALL_NECESSARY;
    privset.Privilege[0].Luid = RtlConvertLongToLuid(SE_MANAGE_VOLUME_PRIVILEGE);
    privset.Privilege[0].Attributes = 0;

    return SePrivilegeCheck(&privset, &access_state->SubjectSecurityContext, processor_mode) ? true : false;
}
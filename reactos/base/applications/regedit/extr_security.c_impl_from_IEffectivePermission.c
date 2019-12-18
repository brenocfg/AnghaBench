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
struct IEffectivePermission {int dummy; } ;
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  PCRegKeySecurity ;

/* Variables and functions */
 int /*<<< orphan*/  CRegKeySecurity ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpIEffectivePermissionVtbl ; 

__attribute__((used)) static __inline PCRegKeySecurity
impl_from_IEffectivePermission(struct IEffectivePermission *iface)
{
    return (PCRegKeySecurity)((ULONG_PTR)iface - FIELD_OFFSET(CRegKeySecurity,
                                                              lpIEffectivePermissionVtbl));
}
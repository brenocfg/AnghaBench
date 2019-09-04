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
struct IDataObject {int dummy; } ;
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  PCDevSettings ;

/* Variables and functions */
 int /*<<< orphan*/  CDevSettings ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpIDataObjectVtbl ; 

__attribute__((used)) static __inline PCDevSettings
impl_from_IDataObject(struct IDataObject *iface)
{
    return (PCDevSettings)((ULONG_PTR)iface - FIELD_OFFSET(CDevSettings,
                                                           lpIDataObjectVtbl));
}
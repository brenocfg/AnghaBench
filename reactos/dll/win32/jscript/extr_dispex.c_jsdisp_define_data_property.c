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
struct TYPE_3__ {unsigned int member_0; unsigned int member_1; int /*<<< orphan*/  value; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_1__ property_desc_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  jsdisp_define_property (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*) ; 

HRESULT jsdisp_define_data_property(jsdisp_t *obj, const WCHAR *name, unsigned flags, jsval_t value)
{
    property_desc_t prop_desc = { flags, flags, TRUE };
    prop_desc.value = value;
    return jsdisp_define_property(obj, name, &prop_desc);
}
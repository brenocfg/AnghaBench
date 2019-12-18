#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_5__ {int /*<<< orphan*/  ref; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  TYPE_2__ dispex_prop_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  PROP_PROTREF ; 
 TYPE_2__* alloc_prop (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dispex_prop_t *alloc_protref(jsdisp_t *This, const WCHAR *name, DWORD ref)
{
    dispex_prop_t *ret;

    ret = alloc_prop(This, name, PROP_PROTREF, 0);
    if(!ret)
        return NULL;

    ret->u.ref = ref;
    return ret;
}
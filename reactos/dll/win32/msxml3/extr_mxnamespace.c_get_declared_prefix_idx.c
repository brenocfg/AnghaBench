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
struct nscontext {size_t count; TYPE_1__* ns; } ;
struct TYPE_2__ {int /*<<< orphan*/ * prefix; } ;
typedef  size_t LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT get_declared_prefix_idx(const struct nscontext *ctxt, LONG index, BSTR *prefix)
{
    *prefix = NULL;

    if (index >= ctxt->count || index < 0) return E_FAIL;

    if (index > 0) index = ctxt->count - index;
    *prefix = ctxt->ns[index].prefix;

    return S_OK;
}
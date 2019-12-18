#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* desc; } ;
typedef  TYPE_3__ vbdisp_t ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_6__ {TYPE_1__* ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  err_number; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_UNEXPECTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static HRESULT Err_Clear(vbdisp_t *This, VARIANT *args, unsigned args_cnt, VARIANT *res)
{
    TRACE("\n");

    if(!This->desc)
        return E_UNEXPECTED;

    This->desc->ctx->err_number = S_OK;
    return S_OK;
}
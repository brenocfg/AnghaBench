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
struct TYPE_3__ {int length; int allocated; scalar_t__ attr; } ;
typedef  TYPE_1__ mxattributes ;
typedef  int /*<<< orphan*/  mxattribute ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ heap_realloc (scalar_t__,int) ; 

__attribute__((used)) static HRESULT mxattributes_grow(mxattributes *This)
{
    if (This->length < This->allocated) return S_OK;

    This->allocated *= 2;
    This->attr = heap_realloc(This->attr, This->allocated*sizeof(mxattribute));

    return This->attr ? S_OK : E_OUTOFMEMORY;
}
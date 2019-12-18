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
struct TYPE_3__ {int /*<<< orphan*/  IMimeBody_iface; } ;
typedef  TYPE_1__ MimeBody ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_1__* mimebody_create () ; 

HRESULT MimeBody_create(IUnknown *outer, void **ppv)
{
    MimeBody *mb;

    if(outer)
        return CLASS_E_NOAGGREGATION;

    if ((mb = mimebody_create()))
    {
        *ppv = &mb->IMimeBody_iface;
        return S_OK;
    }
    else
    {
        *ppv = NULL;
        return E_OUTOFMEMORY;
    }
}
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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  mime_allocator ; 

HRESULT MimeAllocator_create(IUnknown *outer, void **obj)
{
    if(outer) return CLASS_E_NOAGGREGATION;

    *obj = &mime_allocator;
    return S_OK;
}
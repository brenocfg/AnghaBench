#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* lpadesc; TYPE_2__* lptdesc; } ;
struct TYPE_7__ {int vt; TYPE_1__ u; } ;
typedef  TYPE_2__ TYPEDESC ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (TYPE_2__*) ; 
#define  VT_CARRAY 130 
#define  VT_PTR 129 
#define  VT_SAFEARRAY 128 
 int /*<<< orphan*/  free_embedded_arraydesc (TYPE_2__*) ; 

__attribute__((used)) static void free_embedded_typedesc(TYPEDESC *tdesc)
{
    switch(tdesc->vt)
    {
    case VT_PTR:
    case VT_SAFEARRAY:
        free_embedded_typedesc(tdesc->u.lptdesc);
        CoTaskMemFree(tdesc->u.lptdesc);
        break;
    case VT_CARRAY:
        free_embedded_arraydesc(tdesc->u.lpadesc);
        CoTaskMemFree(tdesc->u.lpadesc);
        break;
    }
}
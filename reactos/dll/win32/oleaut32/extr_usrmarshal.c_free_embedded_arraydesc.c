#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* lpadesc; TYPE_3__* lptdesc; } ;
struct TYPE_8__ {int vt; TYPE_1__ u; } ;
struct TYPE_9__ {TYPE_2__ tdescElem; } ;
typedef  TYPE_3__ ARRAYDESC ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (TYPE_3__*) ; 
#define  VT_CARRAY 130 
#define  VT_PTR 129 
#define  VT_SAFEARRAY 128 
 int /*<<< orphan*/  free_embedded_typedesc (TYPE_3__*) ; 

__attribute__((used)) static void free_embedded_arraydesc(ARRAYDESC *adesc)
{
    switch(adesc->tdescElem.vt)
    {
    case VT_PTR:
    case VT_SAFEARRAY:
        free_embedded_typedesc(adesc->tdescElem.u.lptdesc);
        CoTaskMemFree(adesc->tdescElem.u.lptdesc);
        break;
    case VT_CARRAY:
        free_embedded_arraydesc(adesc->tdescElem.u.lpadesc);
        CoTaskMemFree(adesc->tdescElem.u.lpadesc);
        break;
    }
}
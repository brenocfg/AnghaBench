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
struct TYPE_3__ {int /*<<< orphan*/  ITextDocument2Old_iface; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  TYPE_1__ IRichEditOleImpl ;
typedef  int /*<<< orphan*/  IRichEditOle ;

/* Variables and functions */
 TYPE_1__* impl_from_IRichEditOle (int /*<<< orphan*/ *) ; 

void ME_GetITextDocument2OldInterface(IRichEditOle *iface, LPVOID *ppvObj)
{
    IRichEditOleImpl *This = impl_from_IRichEditOle(iface);
    *ppvObj = &This->ITextDocument2Old_iface;
}
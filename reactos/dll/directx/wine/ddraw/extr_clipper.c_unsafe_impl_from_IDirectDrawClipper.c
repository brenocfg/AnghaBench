#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ddraw_clipper {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
typedef  TYPE_1__ IDirectDrawClipper ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ddraw_clipper_vtbl ; 
 struct ddraw_clipper* impl_from_IDirectDrawClipper (TYPE_1__*) ; 

struct ddraw_clipper *unsafe_impl_from_IDirectDrawClipper(IDirectDrawClipper *iface)
{
    if (!iface)
        return NULL;
    assert(iface->lpVtbl == &ddraw_clipper_vtbl);

    return impl_from_IDirectDrawClipper(iface);
}
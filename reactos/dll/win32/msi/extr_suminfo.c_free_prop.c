#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pszVal; } ;
struct TYPE_5__ {scalar_t__ vt; TYPE_1__ u; } ;
typedef  TYPE_2__ PROPVARIANT ;

/* Variables and functions */
 scalar_t__ VT_EMPTY ; 
 scalar_t__ VT_LPSTR ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_prop( PROPVARIANT *prop )
{
    if (prop->vt == VT_LPSTR )
        msi_free( prop->u.pszVal );
    prop->vt = VT_EMPTY;
}
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
struct ra {int dummy; } ;
typedef  enum ra_vartype { ____Placeholder_ra_vartype } ra_vartype ;

/* Variables and functions */
 int RA_VARTYPE_BUF_RW ; 
 int RA_VARTYPE_IMG_W ; 

__attribute__((used)) static int desc_namespace(struct ra *ra, enum ra_vartype type)
{
    // Images and SSBOs both use UAV bindings
    if (type == RA_VARTYPE_IMG_W)
        type = RA_VARTYPE_BUF_RW;
    return type;
}
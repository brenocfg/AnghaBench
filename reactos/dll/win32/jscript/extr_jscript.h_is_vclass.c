#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  jsdisp; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  TYPE_2__ vdisp_t ;
typedef  int /*<<< orphan*/  jsclass_t ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ is_class (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_jsdisp (TYPE_2__*) ; 

__attribute__((used)) static inline BOOL is_vclass(vdisp_t *vdisp, jsclass_t class)
{
    return is_jsdisp(vdisp) && is_class(vdisp->u.jsdisp, class);
}
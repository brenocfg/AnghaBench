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
typedef  int /*<<< orphan*/  DateInstance ;

/* Variables and functions */
 int /*<<< orphan*/  JSCLASS_DATE ; 
 int /*<<< orphan*/ * date_from_jsdisp (int /*<<< orphan*/ ) ; 
 scalar_t__ is_vclass (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline DateInstance *date_this(vdisp_t *jsthis)
{
    return is_vclass(jsthis, JSCLASS_DATE) ? date_from_jsdisp(jsthis->u.jsdisp) : NULL;
}
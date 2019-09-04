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
struct TYPE_3__ {int cd_num; int /*<<< orphan*/ * cd_props; } ;
typedef  int /*<<< orphan*/  AVal ;
typedef  TYPE_1__ AMF3ClassDef ;

/* Variables and functions */
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

void
AMF3CD_AddProp(AMF3ClassDef *cd, AVal *prop)
{
    if (!(cd->cd_num & 0x0f))
        cd->cd_props = realloc(cd->cd_props, (cd->cd_num + 16) * sizeof(AVal));
    cd->cd_props[cd->cd_num++] = *prop;
}
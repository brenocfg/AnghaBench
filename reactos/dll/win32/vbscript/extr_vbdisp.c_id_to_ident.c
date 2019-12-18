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
typedef  int /*<<< orphan*/  ident_map_t ;
struct TYPE_3__ {scalar_t__ ident_map_cnt; scalar_t__ ident_map; } ;
typedef  TYPE_1__ ScriptDisp ;
typedef  scalar_t__ DISPID ;

/* Variables and functions */

__attribute__((used)) static inline ident_map_t *id_to_ident(ScriptDisp *This, DISPID id)
{
    return 0 < id && id <= This->ident_map_cnt ? This->ident_map+id-1 : NULL;
}
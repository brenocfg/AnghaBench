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
struct TYPE_3__ {int /*<<< orphan*/ * ident_map; } ;
typedef  TYPE_1__ ScriptDisp ;
typedef  int DISPID ;

/* Variables and functions */

__attribute__((used)) static inline DISPID ident_to_id(ScriptDisp *This, ident_map_t *ident)
{
    return (ident-This->ident_map)+1;
}
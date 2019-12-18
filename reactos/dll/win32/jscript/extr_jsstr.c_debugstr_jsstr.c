#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsstr_t ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/ * left; } ;

/* Variables and functions */
 char const* debugstr_wn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* jsstr_as_heap (int /*<<< orphan*/ *) ; 
 TYPE_2__* jsstr_as_inline (int /*<<< orphan*/ *) ; 
 TYPE_1__* jsstr_as_rope (int /*<<< orphan*/ *) ; 
 scalar_t__ jsstr_is_heap (int /*<<< orphan*/ *) ; 
 scalar_t__ jsstr_is_inline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_length (int /*<<< orphan*/ *) ; 
 char const* wine_dbg_sprintf (char*,char const*) ; 

const char *debugstr_jsstr(jsstr_t *str)
{
    return jsstr_is_inline(str) ? debugstr_wn(jsstr_as_inline(str)->buf, jsstr_length(str))
        : jsstr_is_heap(str) ? debugstr_wn(jsstr_as_heap(str)->buf, jsstr_length(str))
        : wine_dbg_sprintf("%s...", debugstr_jsstr(jsstr_as_rope(str)->left));
}
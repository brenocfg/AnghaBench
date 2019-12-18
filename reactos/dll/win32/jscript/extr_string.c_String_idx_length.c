#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_6__ {TYPE_1__* ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  str; TYPE_2__ dispex; } ;
struct TYPE_5__ {int version; } ;
typedef  TYPE_3__ StringInstance ;

/* Variables and functions */
 int jsstr_length (int /*<<< orphan*/ ) ; 
 TYPE_3__* string_from_jsdisp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned String_idx_length(jsdisp_t *jsdisp)
{
    StringInstance *string = string_from_jsdisp(jsdisp);

    /*
     * NOTE: For invoke version < 2, indexed array is not implemented at all.
     * Newer jscript.dll versions implement it on string type, not class,
     * which is not how it should work according to spec. IE9 implements it
     * properly, but it uses its own JavaScript engine inside MSHTML. We
     * implement it here, but in the way IE9 and spec work.
     */
    return string->dispex.ctx->version < 2 ? 0 : jsstr_length(string->str);
}
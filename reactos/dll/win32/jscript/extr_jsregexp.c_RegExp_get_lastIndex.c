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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_3__ {int /*<<< orphan*/  last_index_val; } ;
typedef  TYPE_1__ RegExpInstance ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  jsval_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* regexp_from_jsdisp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT RegExp_get_lastIndex(script_ctx_t *ctx, jsdisp_t *jsthis, jsval_t *r)
{
    RegExpInstance *regexp = regexp_from_jsdisp(jsthis);

    TRACE("\n");

    return jsval_copy(regexp->last_index_val, r);
}
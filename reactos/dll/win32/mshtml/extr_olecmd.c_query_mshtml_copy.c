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
struct TYPE_3__ {int cmdf; } ;
typedef  TYPE_1__ OLECMD ;
typedef  int /*<<< orphan*/  HTMLDocument ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ *) ; 
 int OLECMDF_ENABLED ; 
 int OLECMDF_SUPPORTED ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT query_mshtml_copy(HTMLDocument *This, OLECMD *cmd)
{
    FIXME("(%p)\n", This);
    cmd->cmdf = OLECMDF_SUPPORTED|OLECMDF_ENABLED;
    return S_OK;
}
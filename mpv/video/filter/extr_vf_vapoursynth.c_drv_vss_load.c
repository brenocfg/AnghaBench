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
struct priv {int /*<<< orphan*/  se; int /*<<< orphan*/  out_node; int /*<<< orphan*/  script_path; } ;
typedef  int /*<<< orphan*/  VSMap ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct priv*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vsscript_evaluateFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsscript_getError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsscript_getOutput (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsscript_setVariable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drv_vss_load(struct priv *p, VSMap *vars)
{
    vsscript_setVariable(p->se, vars);

    if (vsscript_evaluateFile(&p->se, p->script_path, 0)) {
        MP_FATAL(p, "Script evaluation failed:\n%s\n", vsscript_getError(p->se));
        return -1;
    }
    p->out_node = vsscript_getOutput(p->se, 0);
    return 0;
}
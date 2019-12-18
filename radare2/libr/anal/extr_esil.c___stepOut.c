#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  address; scalar_t__ (* cmd ) (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ RAnalEsil ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __stepOut(RAnalEsil *esil, const char *cmd) {
	static bool inCmdStep = false;
	if (cmd && esil && esil->cmd && !inCmdStep) {
		inCmdStep = true;
		if (esil->cmd (esil, cmd, esil->address, 0)) {
			inCmdStep = false;
			// if returns 1 we skip the impl
			return true;
		}
		inCmdStep = false;
	}
	return false;
}
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
struct TYPE_6__ {char* mnemonic; TYPE_1__* operands; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ArmOp ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_NOTYPE ; 
 int parseOperands (char*,TYPE_2__*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static bool parseOpcode(const char *str, ArmOp *op) {
	char *in = strdup (str);
	char *space = strchr (in, ' ');
	if (!space) {
		op->operands[0].type = ARM_NOTYPE;
		op->mnemonic = in;
 		return true;
	}
	space[0] = '\0';
	op->mnemonic = in;
	space ++;
	return parseOperands (space, op);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_5__ {int /*<<< orphan*/  regread; int /*<<< orphan*/  regs; int /*<<< orphan*/  inputregs; int /*<<< orphan*/  regwrite; } ;
struct TYPE_4__ {TYPE_2__* user; } ;
typedef  TYPE_1__ RAnalEsil ;
typedef  TYPE_2__ AeaStats ;

/* Variables and functions */
 int /*<<< orphan*/  IS_DIGIT (char const) ; 
 int /*<<< orphan*/  contains (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_list_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static int myregread(RAnalEsil *esil, const char *name, ut64 *val, int *len) {
	AeaStats *stats = esil->user;
	if (!IS_DIGIT (*name)) {
		if (!contains (stats->inputregs, name)) {
			if (!contains (stats->regwrite, name)) {
				r_list_push (stats->inputregs, strdup (name));
			}
		}
		if (!contains (stats->regs, name)) {
			r_list_push (stats->regs, strdup (name));
		}
		if (!contains (stats->regread, name)) {
			r_list_push (stats->regread, strdup (name));
		}
	}
	return 0;
}
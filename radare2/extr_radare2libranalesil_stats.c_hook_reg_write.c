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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {int /*<<< orphan*/  stats; } ;
typedef  TYPE_1__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  sdb_array_add (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hook_reg_write(RAnalEsil *esil, const char *name, ut64 *val) {
	sdb_array_add (esil->stats, "reg.write", name, 0);
	return 0;
}
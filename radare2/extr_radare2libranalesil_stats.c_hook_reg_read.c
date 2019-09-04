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
 int /*<<< orphan*/  sdb_array_add (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hook_reg_read(RAnalEsil *esil, const char *name, ut64 *res, int *size) {
	const char *key = (*name>='0' && *name<='9')? "num.load": "reg.read";
	sdb_array_add (esil->stats, key, name, 0);
	return 0;
}
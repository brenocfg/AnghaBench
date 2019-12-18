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
typedef  int /*<<< orphan*/  parse_mnem_args ;
typedef  TYPE_1__* ftable ;
struct TYPE_3__ {int args; int /*<<< orphan*/  res; scalar_t__ pattern; } ;

/* Variables and functions */
 scalar_t__ pattern_match (char const*,scalar_t__) ; 

__attribute__((used)) static parse_mnem_args match_prefix_f(int*args, char const*str, ftable const tbl) {
	int row = 0;
	while (tbl[row].pattern) {
		if (pattern_match (str, tbl[row].pattern)) {
			*args = tbl[row].args;
			return tbl[row].res;
		}
		else {
			row += 1;
		}
	}
	*args = tbl[row].args;
	return tbl[row].res;
}
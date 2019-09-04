#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dso_to_list; int /*<<< orphan*/  dso_from_list; int /*<<< orphan*/  sym_to_list; int /*<<< orphan*/  sym_from_list; int /*<<< orphan*/  comm_list; int /*<<< orphan*/  dso_list; int /*<<< orphan*/  sym_list; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  HISTC_COMM 134 
#define  HISTC_DSO 133 
#define  HISTC_DSO_FROM 132 
#define  HISTC_DSO_TO 131 
#define  HISTC_SYMBOL 130 
#define  HISTC_SYMBOL_FROM 129 
#define  HISTC_SYMBOL_TO 128 
 scalar_t__ SORT_MODE__BRANCH ; 
 int __get_elide (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ sort__mode ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static bool get_elide(int idx, FILE *output)
{
	switch (idx) {
	case HISTC_SYMBOL:
		return __get_elide(symbol_conf.sym_list, "symbol", output);
	case HISTC_DSO:
		return __get_elide(symbol_conf.dso_list, "dso", output);
	case HISTC_COMM:
		return __get_elide(symbol_conf.comm_list, "comm", output);
	default:
		break;
	}

	if (sort__mode != SORT_MODE__BRANCH)
		return false;

	switch (idx) {
	case HISTC_SYMBOL_FROM:
		return __get_elide(symbol_conf.sym_from_list, "sym_from", output);
	case HISTC_SYMBOL_TO:
		return __get_elide(symbol_conf.sym_to_list, "sym_to", output);
	case HISTC_DSO_FROM:
		return __get_elide(symbol_conf.dso_from_list, "dso_from", output);
	case HISTC_DSO_TO:
		return __get_elide(symbol_conf.dso_to_list, "dso_to", output);
	default:
		break;
	}

	return false;
}
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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_block_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_cmd0 (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_core_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_num_get (int /*<<< orphan*/ *,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void foreach_pairs(RCore *core, const char *cmd, const char *each) {
	const char *arg;
	int pair = 0;
	for (arg = each ; ; ) {
		char *next = strchr (arg, ' ');
		if (next) {
			*next = 0;
		}
		if (arg && *arg) {
			ut64 n = r_num_get (NULL, arg);
			if (pair%2) {
				r_core_block_size (core, n);
				r_core_cmd0 (core, cmd);
			} else {
				r_core_seek (core, n, 1);
			}
			pair++;
		}
		if (!next) {
			break;
		}
		arg = next + 1;
	}
}
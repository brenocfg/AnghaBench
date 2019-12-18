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
struct TYPE_3__ {int /*<<< orphan*/  anal; int /*<<< orphan*/  config; } ;
typedef  int /*<<< orphan*/  RSignOptions ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  help_msg_zc ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int r_sign_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int r_sign_diff_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  r_sign_options_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_sign_options_new (char const*,char const*) ; 

__attribute__((used)) static int cmdCompare(void *data, const char *input) {
	int result = true;
	RCore *core = (RCore *) data;
	const char *raw_bytes_thresh = r_config_get (core->config, "zign.diff.bthresh");
	const char *raw_graph_thresh = r_config_get (core->config, "zign.diff.gthresh");
	RSignOptions *options = r_sign_options_new (raw_bytes_thresh, raw_graph_thresh);

	switch (*input) {
	case ' ':
		if (!input[1]) {
			eprintf ("usage: zc other_space\n");
			result = false;
			break;
		}
		result = r_sign_diff (core->anal, options, input + 1);
		break;
	case 'n':
		switch (input[1]) {
		case ' ':
			if (!input[2]) {
				eprintf ("usage: zcn other_space\n");
				result = false;
				break;
			}
			result = r_sign_diff_by_name (core->anal, options, input + 2, false);
			break;
		case '!':
			if (input[2] != ' ' || !input[3]) {
				eprintf ("usage: zcn! other_space\n");
				result = false;
				break;
			}
			result = r_sign_diff_by_name (core->anal, options, input + 3, true);
			break;
		default:
			eprintf ("usage: zcn! other_space\n");
			result = false;
		}
		break;
	case '?':
		r_core_cmd_help (core, help_msg_zc);
		break;
	default:
		eprintf ("usage: zc[?n!] other_space\n");
		result = false;
	}

	r_sign_options_free (options);

	return result;
}
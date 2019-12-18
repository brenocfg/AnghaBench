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
struct TYPE_4__ {int /*<<< orphan*/  priv_data; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_OPT_SEARCH_CHILDREN ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ av_opt_set (TYPE_1__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static bool parse_params(AVCodecContext *context, char **opts)
{
	bool ret = true;

	if (!context || !context->priv_data)
		return true;

	while (*opts) {
		char *opt = *opts;
		char *assign = strchr(opt, '=');

		if (assign) {
			char *name = opt;
			char *value;

			*assign = 0;
			value = assign + 1;

			if (av_opt_set(context, name, value,
				       AV_OPT_SEARCH_CHILDREN)) {
				blog(LOG_WARNING, "Failed to set %s=%s", name,
				     value);
				ret = false;
			}
		}

		opts++;
	}

	return ret;
}
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
struct TYPE_6__ {TYPE_1__* rfs; } ;
struct TYPE_5__ {char** cwd; } ;
typedef  int /*<<< orphan*/  RLineCompletion ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  autocomplete_ms_path (int /*<<< orphan*/ *,TYPE_2__*,char const*,char const*) ; 
 int /*<<< orphan*/  r_return_if_fail (char const*) ; 
 char* r_str_trim_ro (char*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void autocomplete_ms_file(RCore* core, RLineCompletion *completion, const char *str) {
	r_return_if_fail (str);
	char *pipe = strchr (str, '>');
	char *path = (core->rfs && *(core->rfs->cwd)) ? *(core->rfs->cwd): "/";
	if (pipe) {
		str = r_str_trim_ro (pipe + 1);
	}
	if (str && !*str) {
		autocomplete_ms_path (completion, core, str, path);
	} else {
		autocomplete_ms_path (completion, core, str, str);
	}
}
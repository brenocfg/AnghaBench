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
struct TYPE_4__ {int /*<<< orphan*/  lang; } ;
typedef  int /*<<< orphan*/  RLang ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_sysenv_begin (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int r_lang_run_file (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int lang_run_file(RCore *core, RLang *lang, const char *file) {
	r_core_sysenv_begin (core, NULL);
	return r_lang_run_file (core->lang, file);
}
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
struct TYPE_6__ {int /*<<< orphan*/  lang; } ;
struct TYPE_5__ {char* name; } ;
typedef  TYPE_1__ RLangPlugin ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ r_cons_is_interactive () ; 
 TYPE_1__* r_lang_get_by_extension (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_lang_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_lang_prompt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_lang_run_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_lang_run_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_lang_setup (int /*<<< orphan*/ ) ; 
 scalar_t__ r_lang_use (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ r_sandbox_enable (int /*<<< orphan*/ ) ; 
 char* r_str_trim (char*) ; 
 char* strchr (char const*,char) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int cmd_hash_bang (RCore *core, const char *input) {
	char *p;
	const char *lang = input + 1;
	if (r_sandbox_enable (0)) {
		eprintf ("hashbang disabled in sandbox mode\n");
		return false;
	}
	if (*lang=='/') {
		const char *ptr = lang + 1;
		while (*lang) {
			if (*lang=='/') {
				ptr = lang + 1;
			}
			lang++;
		}
		RLangPlugin *p = r_lang_get_by_extension (core->lang, ptr);
		if (p && p->name) {
			lang = p->name;
		}
	}
	if (*lang == ' ') {
		RLangPlugin *p = r_lang_get_by_extension (core->lang, input + 2);
		if (p && p->name) {
			lang = p->name;
		}
	} else if (input[1]=='?' || input[1]=='*' || input[1]=='\0') {
		r_lang_list (core->lang);
		return true;
	}
	if (lang && !*lang) {
		// do nothing
		return true;
	}
	p = strchr (input, ' ');
	bool doEval = false;
	if (p) {
		*p++ = 0;
		char *_e = strstr (p, "-e");
		if (_e) {
			doEval = true;
			p = _e + 2;
			p = r_str_trim (p);
		}
	}
	// TODO: set argv here
	if (r_lang_use (core->lang, lang)) {
		r_lang_setup (core->lang);
		if (p) {
			if (doEval) {
				r_lang_run_string (core->lang, p);
			} else {
				r_lang_run_file (core->lang, p);
			}
		} else {
			if (r_cons_is_interactive ()) {
				r_lang_prompt (core->lang);
			} else {
				eprintf ("Error: scr.interactive required to run the rlang prompt\n");
			}
		}
	} else {
		eprintf ("Invalid hashbang. Please install the corresponding rlang plugin.\nSee '#!' for help.\n");
	}
	return true;
}
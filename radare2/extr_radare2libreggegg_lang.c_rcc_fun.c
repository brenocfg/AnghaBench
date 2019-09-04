#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* dstvar; char* setenviron; char* syscallbody; char* dstval; char* includefile; void* mode; scalar_t__ ndstval; scalar_t__ slurp; int /*<<< orphan*/  callname; } ;
struct TYPE_11__ {TYPE_1__ lang; TYPE_2__* remit; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* call ) (TYPE_3__*,char const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* comment ) (TYPE_3__*,char*,scalar_t__,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ REggEmit ;
typedef  TYPE_3__ REgg ;

/* Variables and functions */
 void* ALIAS ; 
 scalar_t__ CTX ; 
 void* DATA ; 
 void* GOTO ; 
 void* INCLUDE ; 
 void* INLINE ; 
 void* NAKED ; 
 void* NORMAL ; 
 int /*<<< orphan*/  R_FREE (char*) ; 
 void* SYSCALL ; 
 int /*<<< orphan*/  eprintf (char*,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_space (char) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  r_egg_printf (TYPE_3__*,char*,char const*,...) ; 
 int /*<<< orphan*/  rcc_set_callname (TYPE_3__*,char*) ; 
 char* skipspaces (char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 void* strdup (char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcc_fun(REgg *egg, const char *str) {
	char *ptr, *ptr2;
	REggEmit *e = egg->remit;
	str = skipspaces (str);
	if (CTX) {
		ptr = strchr (str, '=');
		if (ptr) {
			*ptr++ = '\0';
			free (egg->lang.dstvar);
			egg->lang.dstvar = strdup (skipspaces (str));
			ptr2 = (char *) skipspaces (ptr);
			if (*ptr2) {
				rcc_set_callname (egg, skipspaces (ptr));
			}
		} else {
			str = skipspaces (str);
			rcc_set_callname (egg, skipspaces (str));
			egg->remit->comment (egg, "rcc_fun %d (%s)",
				CTX, egg->lang.callname);
		}
	} else {
		ptr = strchr (str, '@');
		if (ptr) {
			*ptr++ = '\0';
			egg->lang.mode = NORMAL;
			if (strstr (ptr, "env")) {
				// eprintf ("SETENV (%s)\n", str);
				free (egg->lang.setenviron);
				egg->lang.setenviron = strdup (skipspaces (str));
				egg->lang.slurp = 0;
			} else if (strstr (ptr, "fastcall")) {
				/* TODO : not yet implemented */
			} else if (strstr (ptr, "syscall")) {
				if (*str) {
					egg->lang.mode = SYSCALL;
					egg->lang.dstvar = strdup (skipspaces (str));
				} else {
					egg->lang.mode = INLINE;
					free (egg->lang.syscallbody);
					egg->lang.syscallbody = malloc (4096);	// XXX hardcoded size
					egg->lang.dstval = egg->lang.syscallbody;
					R_FREE (egg->lang.dstvar);
					egg->lang.ndstval = 0;
					*egg->lang.syscallbody = '\0';
				}
			} else if (strstr (ptr, "include")) {
				egg->lang.mode = INCLUDE;
				free (egg->lang.includefile);
				egg->lang.includefile = strdup (skipspaces (str));
				// egg->lang.slurp = 0;
				// try to deal with alias
			} else if (strstr (ptr, "alias")) {
				egg->lang.mode = ALIAS;
				ptr2 = egg->lang.dstvar = strdup (skipspaces (str));
				while (*ptr2 && !is_space (*ptr2)) {
					ptr2++;
				}
				*ptr2 = '\x00';
				// for aliases must be valid and accurate strings
			} else if (strstr (ptr, "data")) {
				egg->lang.mode = DATA;
				egg->lang.ndstval = 0;
				egg->lang.dstvar = strdup (skipspaces (str));
				egg->lang.dstval = malloc (4096);
			} else if (strstr (ptr, "naked")) {
				egg->lang.mode = NAKED;
				/*
				free (egg->lang.dstvar);
				egg->lang.dstvar = strdup (skipspaces (str));
				egg->lang.dstval = malloc (4096);
				egg->lang.ndstval = 0;
				*/
				r_egg_printf (egg, "%s:\n", str);
			} else if (strstr (ptr, "inline")) {
				egg->lang.mode = INLINE;
				free (egg->lang.dstvar);
				egg->lang.dstvar = strdup (skipspaces (str));
				egg->lang.dstval = malloc (4096);
				egg->lang.ndstval = 0;
			} else {
				// naked label
				if (*ptr) {
					r_egg_printf (egg, "\n.%s %s\n", ptr, str);
				}
				r_egg_printf (egg, "%s:\n", str);
			}
		} else {
			// e->jmp (egg, egg->lang.ctxpush[context], 0);
			if (CTX > 0) {
				// WTF?
				eprintf ("LABEL %d\n", CTX);
				r_egg_printf (egg, "\n%s:\n", str);
			} else {
				if (!strcmp (str, "goto")) {
					egg->lang.mode = GOTO;
				} else {
					// call() // or maybe jmp?
					e->call (egg, str, 0);
				}
			}
		}
	}
}
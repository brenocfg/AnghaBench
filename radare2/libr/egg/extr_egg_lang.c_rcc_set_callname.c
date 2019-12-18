#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int pushargs; int /*<<< orphan*/  callname; scalar_t__ nargs; } ;
struct TYPE_5__ {TYPE_1__ lang; } ;
typedef  TYPE_2__ REgg ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skipspaces (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trim (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcc_set_callname(REgg *egg, const char *s) {
	R_FREE (egg->lang.callname);
	egg->lang.nargs = 0;
	egg->lang.callname = trim (strdup (skipspaces (s)));
	egg->lang.pushargs = !((!strcmp (s, "goto")) || (!strcmp (s, "break")));
}
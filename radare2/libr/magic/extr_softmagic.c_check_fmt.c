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
struct r_magic {int dummy; } ;
typedef  int /*<<< orphan*/  errmsg ;
typedef  int /*<<< orphan*/  RRegex ;
typedef  int /*<<< orphan*/  RMagic ;

/* Variables and functions */
 int /*<<< orphan*/  R_MAGIC_DESC ; 
 int R_REGEX_EXTENDED ; 
 int R_REGEX_NOSUB ; 
 int /*<<< orphan*/  file_magerror (int /*<<< orphan*/ *,char*,int,char*) ; 
 int r_regex_comp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  r_regex_error (int,int /*<<< orphan*/ *,char*,int) ; 
 int r_regex_exec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_regex_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int check_fmt(RMagic *ms, struct r_magic *m) {
	RRegex rx;
	int rc;

	if (!strchr (R_MAGIC_DESC, '%')) {
		return 0;
	}

	rc = r_regex_comp (&rx, "%[-0-9\\.]*s", R_REGEX_EXTENDED|R_REGEX_NOSUB);
	if (rc) {
		char errmsg[512];
		r_regex_error (rc, &rx, errmsg, sizeof (errmsg) - 1);
		file_magerror (ms, "regex error %d, (%s)", rc, errmsg);
		return -1;
	} else {
		rc = r_regex_exec (&rx, R_MAGIC_DESC, 0, 0, 0);
		r_regex_fini (&rx);
		return !rc;
	}
}
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
typedef  int /*<<< orphan*/  sbuf ;
struct TYPE_4__ {scalar_t__ add; } ;
typedef  TYPE_1__ SdbDiff ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int sdb_diff_format (char*,int,TYPE_1__ const*) ; 

__attribute__((used)) static void dbdiff_cb(const SdbDiff *diff, void *user) {
	char sbuf[512];
	int r = sdb_diff_format (sbuf, sizeof(sbuf), diff);
	if (r < 0) {
		return;
	}
	char *buf = sbuf;
	char *hbuf = NULL;
	if ((size_t)r >= sizeof (sbuf)) {
		hbuf = malloc (r + 1);
		if (!hbuf) {
			return;
		}
		r = sdb_diff_format (hbuf, r + 1, diff);
		if (r < 0) {
			goto beach;
		}
	}
	printf ("\x1b[%sm%s\x1b[0m\n", diff->add ? "32" : "31", buf);
beach:
	free (hbuf);
}
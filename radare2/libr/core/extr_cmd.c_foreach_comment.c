#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* user; TYPE_1__* anal; } ;
struct TYPE_3__ {int /*<<< orphan*/ * user; } ;
typedef  int /*<<< orphan*/  RCore ;
typedef  TYPE_2__ RAnalMetaUserItem ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_core_cmd0 (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_core_cmdf (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ sdb_decode (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int foreach_comment(void *user, const char *k, const char *v) {
	RAnalMetaUserItem *ui = user;
	RCore *core = ui->anal->user;
	const char *cmd = ui->user;
	if (!strncmp (k, "meta.C.", 7)) {
		char *cmt = (char *)sdb_decode (v, 0);
		if (cmt) {
			r_core_cmdf (core, "s %s", k + 7);
			r_core_cmd0 (core, cmd);
			free (cmt);
		}
	}
	return 1;
}
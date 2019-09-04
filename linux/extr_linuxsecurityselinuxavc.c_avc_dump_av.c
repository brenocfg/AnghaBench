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
typedef  int u32 ;
typedef  int u16 ;
struct audit_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  av ;
struct TYPE_3__ {char** perms; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 TYPE_1__* secclass_map ; 

__attribute__((used)) static void avc_dump_av(struct audit_buffer *ab, u16 tclass, u32 av)
{
	const char **perms;
	int i, perm;

	if (av == 0) {
		audit_log_format(ab, " null");
		return;
	}

	BUG_ON(!tclass || tclass >= ARRAY_SIZE(secclass_map));
	perms = secclass_map[tclass-1].perms;

	audit_log_format(ab, " {");
	i = 0;
	perm = 1;
	while (i < (sizeof(av) * 8)) {
		if ((perm & av) && perms[i]) {
			audit_log_format(ab, " %s", perms[i]);
			av &= ~perm;
		}
		i++;
		perm <<= 1;
	}

	if (av)
		audit_log_format(ab, " 0x%x", av);

	audit_log_format(ab, " }");
}
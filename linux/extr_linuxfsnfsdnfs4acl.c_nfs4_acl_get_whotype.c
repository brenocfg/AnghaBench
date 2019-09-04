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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int type; int /*<<< orphan*/  string; int /*<<< orphan*/  stringlen; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int NFS4_ACL_WHO_NAMED ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* s2t_map ; 

int
nfs4_acl_get_whotype(char *p, u32 len)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(s2t_map); i++) {
		if (s2t_map[i].stringlen == len &&
				0 == memcmp(s2t_map[i].string, p, len))
			return s2t_map[i].type;
	}
	return NFS4_ACL_WHO_NAMED;
}
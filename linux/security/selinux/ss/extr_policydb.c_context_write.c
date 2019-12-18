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
typedef  int /*<<< orphan*/  u32 ;
struct policydb {int dummy; } ;
struct context {int /*<<< orphan*/  range; int /*<<< orphan*/  type; int /*<<< orphan*/  role; int /*<<< orphan*/  user; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int mls_write_range_helper (int /*<<< orphan*/ *,void*) ; 
 int put_entry (int /*<<< orphan*/ *,int,int,void*) ; 

__attribute__((used)) static int context_write(struct policydb *p, struct context *c,
			 void *fp)
{
	int rc;
	__le32 buf[3];

	buf[0] = cpu_to_le32(c->user);
	buf[1] = cpu_to_le32(c->role);
	buf[2] = cpu_to_le32(c->type);

	rc = put_entry(buf, sizeof(u32), 3, fp);
	if (rc)
		return rc;

	rc = mls_write_range_helper(&c->range, fp);
	if (rc)
		return rc;

	return 0;
}
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
struct type_set {int /*<<< orphan*/  flags; int /*<<< orphan*/  negset; int /*<<< orphan*/  types; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ ebitmap_write (int /*<<< orphan*/ *,void*) ; 
 int put_entry (int /*<<< orphan*/ *,int,int,void*) ; 

__attribute__((used)) static int type_set_write(struct type_set *t, void *fp)
{
	int rc;
	__le32 buf[1];

	if (ebitmap_write(&t->types, fp))
		return -EINVAL;
	if (ebitmap_write(&t->negset, fp))
		return -EINVAL;

	buf[0] = cpu_to_le32(t->flags);
	rc = put_entry(buf, sizeof(u32), 1, fp);
	if (rc)
		return -EINVAL;

	return 0;
}
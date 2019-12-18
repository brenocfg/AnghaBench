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
 scalar_t__ ebitmap_read (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static int type_set_read(struct type_set *t, void *fp)
{
	__le32 buf[1];
	int rc;

	if (ebitmap_read(&t->types, fp))
		return -EINVAL;
	if (ebitmap_read(&t->negset, fp))
		return -EINVAL;

	rc = next_entry(buf, fp, sizeof(u32));
	if (rc < 0)
		return -EINVAL;
	t->flags = le32_to_cpu(buf[0]);

	return 0;
}
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
struct audit_watch {char* path; int /*<<< orphan*/  ino; int /*<<< orphan*/  dev; int /*<<< orphan*/  count; int /*<<< orphan*/  rules; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_DEV_UNSET ; 
 int /*<<< orphan*/  AUDIT_INO_UNSET ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct audit_watch* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct audit_watch* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct audit_watch *audit_init_watch(char *path)
{
	struct audit_watch *watch;

	watch = kzalloc(sizeof(*watch), GFP_KERNEL);
	if (unlikely(!watch))
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&watch->rules);
	refcount_set(&watch->count, 1);
	watch->path = path;
	watch->dev = AUDIT_DEV_UNSET;
	watch->ino = AUDIT_INO_UNSET;

	return watch;
}
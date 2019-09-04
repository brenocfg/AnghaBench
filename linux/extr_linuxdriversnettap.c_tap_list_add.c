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
struct major_info {char const* device_name; int /*<<< orphan*/  next; int /*<<< orphan*/  minor_lock; int /*<<< orphan*/  minor_idr; int /*<<< orphan*/  major; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 struct major_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  major_list ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tap_list_add(dev_t major, const char *device_name)
{
	struct major_info *tap_major;

	tap_major = kzalloc(sizeof(*tap_major), GFP_ATOMIC);
	if (!tap_major)
		return -ENOMEM;

	tap_major->major = MAJOR(major);

	idr_init(&tap_major->minor_idr);
	spin_lock_init(&tap_major->minor_lock);

	tap_major->device_name = device_name;

	list_add_tail_rcu(&tap_major->next, &major_list);
	return 0;
}
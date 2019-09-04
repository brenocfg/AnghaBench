#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_mutex_t ;
struct TYPE_6__ {char const* name; int /*<<< orphan*/  entry; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ profile_root_entry ;
typedef  int /*<<< orphan*/  profile_entry ;
struct TYPE_7__ {size_t num; TYPE_1__* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  bmalloc (int) ; 
 int /*<<< orphan*/  bzalloc (int) ; 
 TYPE_1__* da_push_back_new (TYPE_2__) ; 
 int /*<<< orphan*/  init_entry (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ root_entries ; 

__attribute__((used)) static profile_root_entry *get_root_entry(const char *name)
{
	profile_root_entry *r_entry = NULL;

	for (size_t i = 0; i < root_entries.num; i++) {
		if (root_entries.array[i].name == name) {
			r_entry = &root_entries.array[i];
			break;
		}
	}

	if (!r_entry) {
		r_entry = da_push_back_new(root_entries);
		r_entry->mutex = bmalloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(r_entry->mutex, NULL);

		r_entry->name = name;
		r_entry->entry = bzalloc(sizeof(profile_entry));
		init_entry(r_entry->entry, name);
	}

	return r_entry;
}
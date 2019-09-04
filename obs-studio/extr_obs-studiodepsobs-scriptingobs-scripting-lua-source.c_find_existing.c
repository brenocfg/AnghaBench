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
struct obs_lua_source {char const* id; struct obs_lua_source* next; } ;

/* Variables and functions */
 struct obs_lua_source* first_source_def ; 
 int /*<<< orphan*/  lua_source_def_mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct obs_lua_source *find_existing(const char *id)
{
	struct obs_lua_source *existing = NULL;

	pthread_mutex_lock(&lua_source_def_mutex);
	struct obs_lua_source *ls = first_source_def;
	while (ls) {
		/* can compare pointers here due to string table */
		if (ls->id == id) {
			existing = ls;
			break;
		}

		ls = ls->next;
	}
	pthread_mutex_unlock(&lua_source_def_mutex);

	return existing;
}
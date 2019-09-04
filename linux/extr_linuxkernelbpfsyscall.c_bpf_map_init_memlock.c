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
struct user_struct {int dummy; } ;
struct bpf_map {struct user_struct* user; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int bpf_charge_memlock (struct user_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_uid (struct user_struct*) ; 
 struct user_struct* get_current_user () ; 

__attribute__((used)) static int bpf_map_init_memlock(struct bpf_map *map)
{
	struct user_struct *user = get_current_user();
	int ret;

	ret = bpf_charge_memlock(user, map->pages);
	if (ret) {
		free_uid(user);
		return ret;
	}
	map->user = user;
	return ret;
}
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
struct bpf_map {int /*<<< orphan*/  pages; struct user_struct* user; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_uncharge_memlock (struct user_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_uid (struct user_struct*) ; 

__attribute__((used)) static void bpf_map_release_memlock(struct bpf_map *map)
{
	struct user_struct *user = map->user;
	bpf_uncharge_memlock(user, map->pages);
	free_uid(user);
}
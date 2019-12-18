#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fd {TYPE_1__* file; } ;
struct bpf_map {int /*<<< orphan*/  frozen; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  f_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_CAN_WRITE ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static fmode_t map_get_sys_perms(struct bpf_map *map, struct fd f)
{
	fmode_t mode = f.file->f_mode;

	/* Our file permissions may have been overridden by global
	 * map permissions facing syscall side.
	 */
	if (READ_ONCE(map->frozen))
		mode &= ~FMODE_CAN_WRITE;
	return mode;
}
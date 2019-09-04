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
struct kcore_copy_info {int dummy; } ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 scalar_t__ elf_read_maps (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct kcore_copy_info*) ; 
 int /*<<< orphan*/  kcore_copy__read_map ; 

__attribute__((used)) static int kcore_copy__read_maps(struct kcore_copy_info *kci, Elf *elf)
{
	if (elf_read_maps(elf, true, kcore_copy__read_map, kci) < 0)
		return -1;

	return 0;
}
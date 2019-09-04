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
struct kcore {int /*<<< orphan*/  fd; int /*<<< orphan*/  elf; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kcore__close(struct kcore *kcore)
{
	elf_end(kcore->elf);
	close(kcore->fd);
}
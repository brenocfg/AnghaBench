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
struct inode {int /*<<< orphan*/  i_dir_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline void end_dir_add(struct inode *dir, unsigned n)
{
	smp_store_release(&dir->i_dir_seq, n + 2);
}
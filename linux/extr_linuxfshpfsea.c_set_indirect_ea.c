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
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  secno ;

/* Variables and functions */
 int /*<<< orphan*/  hpfs_ea_write (struct super_block*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static void set_indirect_ea(struct super_block *s, int ano, secno a,
			    const char *data, int size)
{
	hpfs_ea_write(s, a, ano, 0, size, data);
}
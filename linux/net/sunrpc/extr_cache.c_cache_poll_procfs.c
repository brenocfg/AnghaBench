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
struct file {int dummy; } ;
struct cache_detail {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 struct cache_detail* PDE_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_poll (struct file*,int /*<<< orphan*/ *,struct cache_detail*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 

__attribute__((used)) static __poll_t cache_poll_procfs(struct file *filp, poll_table *wait)
{
	struct cache_detail *cd = PDE_DATA(file_inode(filp));

	return cache_poll(filp, wait, cd);
}
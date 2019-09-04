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
struct file {int dummy; } ;
struct cache_detail {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;
struct TYPE_2__ {struct cache_detail* private; } ;

/* Variables and functions */
 TYPE_1__* RPC_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_poll (struct file*,int /*<<< orphan*/ *,struct cache_detail*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 

__attribute__((used)) static __poll_t cache_poll_pipefs(struct file *filp, poll_table *wait)
{
	struct cache_detail *cd = RPC_I(file_inode(filp))->private;

	return cache_poll(filp, wait, cd);
}
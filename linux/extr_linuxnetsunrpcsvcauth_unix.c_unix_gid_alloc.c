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
struct cache_head {int dummy; } ;
struct unix_gid {struct cache_head h; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct unix_gid* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cache_head *unix_gid_alloc(void)
{
	struct unix_gid *g = kmalloc(sizeof(*g), GFP_KERNEL);
	if (g)
		return &g->h;
	else
		return NULL;
}
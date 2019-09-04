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
struct rsi {struct cache_head h; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rsi* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cache_head *rsi_alloc(void)
{
	struct rsi *rsii = kmalloc(sizeof(*rsii), GFP_KERNEL);
	if (rsii)
		return &rsii->h;
	else
		return NULL;
}
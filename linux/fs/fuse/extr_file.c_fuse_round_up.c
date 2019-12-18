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
struct fuse_conn {int max_pages; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  round_up (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline loff_t fuse_round_up(struct fuse_conn *fc, loff_t off)
{
	return round_up(off, fc->max_pages << PAGE_SHIFT);
}
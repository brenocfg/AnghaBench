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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ B_LEVEL (struct buffer_head const*) ; 
 scalar_t__ FREE_LEVEL ; 
 scalar_t__ MAX_HEIGHT ; 
 int /*<<< orphan*/  RFALSE (int,char*,struct buffer_head const*,struct buffer_head const*) ; 

inline int B_IS_IN_TREE(const struct buffer_head *bh)
{

	RFALSE(B_LEVEL(bh) > MAX_HEIGHT,
	       "PAP-1010: block (%b) has too big level (%z)", bh, bh);

	return (B_LEVEL(bh) != FREE_LEVEL);
}
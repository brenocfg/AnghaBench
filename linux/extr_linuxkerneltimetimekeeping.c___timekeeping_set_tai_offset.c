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
struct timekeeper {int /*<<< orphan*/  offs_real; int /*<<< orphan*/  offs_tai; int /*<<< orphan*/  tai_offset; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __timekeeping_set_tai_offset(struct timekeeper *tk, s32 tai_offset)
{
	tk->tai_offset = tai_offset;
	tk->offs_tai = ktime_add(tk->offs_real, ktime_set(tai_offset, 0));
}
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
typedef  int /*<<< orphan*/  time32_t ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmt_to_local (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 

__attribute__((used)) static inline time32_t local_get_seconds(struct super_block *s)
{
	return gmt_to_local(s, ktime_get_real_seconds());
}
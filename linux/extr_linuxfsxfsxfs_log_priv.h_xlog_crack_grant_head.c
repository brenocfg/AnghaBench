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
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xlog_crack_grant_head_val (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static inline void
xlog_crack_grant_head(atomic64_t *head, int *cycle, int *space)
{
	xlog_crack_grant_head_val(atomic64_read(head), cycle, space);
}
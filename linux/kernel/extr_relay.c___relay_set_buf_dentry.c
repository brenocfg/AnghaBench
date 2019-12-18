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
struct rchan_percpu_buf_dispatcher {int /*<<< orphan*/  dentry; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  relay_set_buf_dentry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __relay_set_buf_dentry(void *info)
{
	struct rchan_percpu_buf_dispatcher *p = info;

	relay_set_buf_dentry(p->buf, p->dentry);
}
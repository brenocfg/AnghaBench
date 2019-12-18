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
struct msg_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 struct msg_msg* ERR_PTR (int /*<<< orphan*/ ) ; 

struct msg_msg *copy_msg(struct msg_msg *src, struct msg_msg *dst)
{
	return ERR_PTR(-ENOSYS);
}
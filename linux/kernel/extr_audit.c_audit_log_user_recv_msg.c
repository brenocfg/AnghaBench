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
typedef  int /*<<< orphan*/  u16 ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_log_common_recv_msg (int /*<<< orphan*/ *,struct audit_buffer**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void audit_log_user_recv_msg(struct audit_buffer **ab,
					   u16 msg_type)
{
	audit_log_common_recv_msg(NULL, ab, msg_type);
}
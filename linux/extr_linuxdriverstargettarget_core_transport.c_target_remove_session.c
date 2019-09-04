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
struct se_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  transport_deregister_session (struct se_session*) ; 
 int /*<<< orphan*/  transport_deregister_session_configfs (struct se_session*) ; 

void target_remove_session(struct se_session *se_sess)
{
	transport_deregister_session_configfs(se_sess);
	transport_deregister_session(se_sess);
}
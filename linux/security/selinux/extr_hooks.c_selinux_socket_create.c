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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct task_security_struct {int /*<<< orphan*/  sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET__CREATE ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_cred () ; 
 struct task_security_struct* selinux_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_state ; 
 int socket_sockcreate_sid (struct task_security_struct const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_type_to_security_class (int,int,int) ; 

__attribute__((used)) static int selinux_socket_create(int family, int type,
				 int protocol, int kern)
{
	const struct task_security_struct *tsec = selinux_cred(current_cred());
	u32 newsid;
	u16 secclass;
	int rc;

	if (kern)
		return 0;

	secclass = socket_type_to_security_class(family, type, protocol);
	rc = socket_sockcreate_sid(tsec, secclass, &newsid);
	if (rc)
		return rc;

	return avc_has_perm(&selinux_state,
			    tsec->sid, newsid, secclass, SOCKET__CREATE, NULL);
}
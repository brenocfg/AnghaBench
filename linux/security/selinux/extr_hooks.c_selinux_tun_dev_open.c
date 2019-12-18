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
struct tun_security_struct {int /*<<< orphan*/  sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECCLASS_TUN_SOCKET ; 
 int /*<<< orphan*/  TUN_SOCKET__RELABELFROM ; 
 int /*<<< orphan*/  TUN_SOCKET__RELABELTO ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_sid () ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_tun_dev_open(void *security)
{
	struct tun_security_struct *tunsec = security;
	u32 sid = current_sid();
	int err;

	err = avc_has_perm(&selinux_state,
			   sid, tunsec->sid, SECCLASS_TUN_SOCKET,
			   TUN_SOCKET__RELABELFROM, NULL);
	if (err)
		return err;
	err = avc_has_perm(&selinux_state,
			   sid, sid, SECCLASS_TUN_SOCKET,
			   TUN_SOCKET__RELABELTO, NULL);
	if (err)
		return err;
	tunsec->sid = sid;

	return 0;
}
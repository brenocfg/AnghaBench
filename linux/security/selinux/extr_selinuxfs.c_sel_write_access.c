#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct selinux_state {int dummy; } ;
struct selinux_fs_info {struct selinux_state* state; } ;
struct file {int dummy; } ;
struct av_decision {int /*<<< orphan*/  flags; int /*<<< orphan*/  seqno; int /*<<< orphan*/  auditdeny; int /*<<< orphan*/  auditallow; int /*<<< orphan*/  allowed; } ;
typedef  int ssize_t ;
struct TYPE_4__ {TYPE_1__* i_sb; } ;
struct TYPE_3__ {struct selinux_fs_info* s_fs_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SECCLASS_SECURITY ; 
 int /*<<< orphan*/  SECINITSID_SECURITY ; 
 int /*<<< orphan*/  SECURITY__COMPUTE_AV ; 
 int /*<<< orphan*/  SIMPLE_TRANSACTION_LIMIT ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_sid () ; 
 TYPE_2__* file_inode (struct file*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_compute_av_user (struct selinux_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct av_decision*) ; 
 int security_context_str_to_sid (struct selinux_state*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_state ; 
 int sscanf (char*,char*,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t sel_write_access(struct file *file, char *buf, size_t size)
{
	struct selinux_fs_info *fsi = file_inode(file)->i_sb->s_fs_info;
	struct selinux_state *state = fsi->state;
	char *scon = NULL, *tcon = NULL;
	u32 ssid, tsid;
	u16 tclass;
	struct av_decision avd;
	ssize_t length;

	length = avc_has_perm(&selinux_state,
			      current_sid(), SECINITSID_SECURITY,
			      SECCLASS_SECURITY, SECURITY__COMPUTE_AV, NULL);
	if (length)
		goto out;

	length = -ENOMEM;
	scon = kzalloc(size + 1, GFP_KERNEL);
	if (!scon)
		goto out;

	length = -ENOMEM;
	tcon = kzalloc(size + 1, GFP_KERNEL);
	if (!tcon)
		goto out;

	length = -EINVAL;
	if (sscanf(buf, "%s %s %hu", scon, tcon, &tclass) != 3)
		goto out;

	length = security_context_str_to_sid(state, scon, &ssid, GFP_KERNEL);
	if (length)
		goto out;

	length = security_context_str_to_sid(state, tcon, &tsid, GFP_KERNEL);
	if (length)
		goto out;

	security_compute_av_user(state, ssid, tsid, tclass, &avd);

	length = scnprintf(buf, SIMPLE_TRANSACTION_LIMIT,
			  "%x %x %x %x %u %x",
			  avd.allowed, 0xffffffff,
			  avd.auditallow, avd.auditdeny,
			  avd.seqno, avd.flags);
out:
	kfree(tcon);
	kfree(scon);
	return length;
}
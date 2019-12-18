#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uid_t ;
struct user_namespace {int dummy; } ;
struct seq_file {TYPE_2__* file; } ;
struct nfsd4_fs_locations {scalar_t__ locations_count; TYPE_3__* locations; scalar_t__ migrated; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  int gid_t ;
struct TYPE_6__ {int /*<<< orphan*/  hosts; int /*<<< orphan*/  path; } ;
struct TYPE_5__ {TYPE_1__* f_cred; } ;
struct TYPE_4__ {struct user_namespace* user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSEXP_ALLFLAGS ; 
 int NFSEXP_FSID ; 
 char* from_kgid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 char* from_kuid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (struct user_namespace*,int) ; 
 int /*<<< orphan*/  make_kuid (struct user_namespace*,int) ; 
 int /*<<< orphan*/  seq_escape (struct seq_file*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  show_expflags (struct seq_file*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exp_flags(struct seq_file *m, int flag, int fsid,
		kuid_t anonu, kgid_t anong, struct nfsd4_fs_locations *fsloc)
{
	struct user_namespace *userns = m->file->f_cred->user_ns;

	show_expflags(m, flag, NFSEXP_ALLFLAGS);
	if (flag & NFSEXP_FSID)
		seq_printf(m, ",fsid=%d", fsid);
	if (!uid_eq(anonu, make_kuid(userns, (uid_t)-2)) &&
	    !uid_eq(anonu, make_kuid(userns, 0x10000-2)))
		seq_printf(m, ",anonuid=%u", from_kuid_munged(userns, anonu));
	if (!gid_eq(anong, make_kgid(userns, (gid_t)-2)) &&
	    !gid_eq(anong, make_kgid(userns, 0x10000-2)))
		seq_printf(m, ",anongid=%u", from_kgid_munged(userns, anong));
	if (fsloc && fsloc->locations_count > 0) {
		char *loctype = (fsloc->migrated) ? "refer" : "replicas";
		int i;

		seq_printf(m, ",%s=", loctype);
		seq_escape(m, fsloc->locations[0].path, ",;@ \t\n\\");
		seq_putc(m, '@');
		seq_escape(m, fsloc->locations[0].hosts, ",;@ \t\n\\");
		for (i = 1; i < fsloc->locations_count; i++) {
			seq_putc(m, ';');
			seq_escape(m, fsloc->locations[i].path, ",;@ \t\n\\");
			seq_putc(m, '@');
			seq_escape(m, fsloc->locations[i].hosts, ",;@ \t\n\\");
		}
	}
}
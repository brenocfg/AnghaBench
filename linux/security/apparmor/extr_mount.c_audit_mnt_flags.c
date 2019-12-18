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
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 unsigned long MS_BIND ; 
 unsigned long MS_DIRSYNC ; 
 unsigned long MS_I_VERSION ; 
 unsigned long MS_MANDLOCK ; 
 unsigned long MS_MOVE ; 
 unsigned long MS_NOATIME ; 
 unsigned long MS_NODEV ; 
 unsigned long MS_NODIRATIME ; 
 unsigned long MS_NOEXEC ; 
 unsigned long MS_NOSUID ; 
 unsigned long MS_NOUSER ; 
 unsigned long MS_POSIXACL ; 
 unsigned long MS_PRIVATE ; 
 unsigned long MS_RDONLY ; 
 unsigned long MS_REC ; 
 unsigned long MS_RELATIME ; 
 unsigned long MS_REMOUNT ; 
 unsigned long MS_SHARED ; 
 unsigned long MS_SILENT ; 
 unsigned long MS_SLAVE ; 
 unsigned long MS_STRICTATIME ; 
 unsigned long MS_SYNCHRONOUS ; 
 unsigned long MS_UNBINDABLE ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*) ; 

__attribute__((used)) static void audit_mnt_flags(struct audit_buffer *ab, unsigned long flags)
{
	if (flags & MS_RDONLY)
		audit_log_format(ab, "ro");
	else
		audit_log_format(ab, "rw");
	if (flags & MS_NOSUID)
		audit_log_format(ab, ", nosuid");
	if (flags & MS_NODEV)
		audit_log_format(ab, ", nodev");
	if (flags & MS_NOEXEC)
		audit_log_format(ab, ", noexec");
	if (flags & MS_SYNCHRONOUS)
		audit_log_format(ab, ", sync");
	if (flags & MS_REMOUNT)
		audit_log_format(ab, ", remount");
	if (flags & MS_MANDLOCK)
		audit_log_format(ab, ", mand");
	if (flags & MS_DIRSYNC)
		audit_log_format(ab, ", dirsync");
	if (flags & MS_NOATIME)
		audit_log_format(ab, ", noatime");
	if (flags & MS_NODIRATIME)
		audit_log_format(ab, ", nodiratime");
	if (flags & MS_BIND)
		audit_log_format(ab, flags & MS_REC ? ", rbind" : ", bind");
	if (flags & MS_MOVE)
		audit_log_format(ab, ", move");
	if (flags & MS_SILENT)
		audit_log_format(ab, ", silent");
	if (flags & MS_POSIXACL)
		audit_log_format(ab, ", acl");
	if (flags & MS_UNBINDABLE)
		audit_log_format(ab, flags & MS_REC ? ", runbindable" :
				 ", unbindable");
	if (flags & MS_PRIVATE)
		audit_log_format(ab, flags & MS_REC ? ", rprivate" :
				 ", private");
	if (flags & MS_SLAVE)
		audit_log_format(ab, flags & MS_REC ? ", rslave" :
				 ", slave");
	if (flags & MS_SHARED)
		audit_log_format(ab, flags & MS_REC ? ", rshared" :
				 ", shared");
	if (flags & MS_RELATIME)
		audit_log_format(ab, ", relatime");
	if (flags & MS_I_VERSION)
		audit_log_format(ab, ", iversion");
	if (flags & MS_STRICTATIME)
		audit_log_format(ab, ", strictatime");
	if (flags & MS_NOUSER)
		audit_log_format(ab, ", nouser");
}
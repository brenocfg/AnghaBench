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
struct syscall_arg {int val; } ;

/* Variables and functions */
 int S_IALLUGO ; 
 int S_IFBLK ; 
 int S_IFCHR ; 
 int S_IFDIR ; 
 int S_IFIFO ; 
 int S_IFLNK ; 
 int S_IFMT ; 
 int S_IFREG ; 
 int S_IFSOCK ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUGO ; 
 int S_IRUSR ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int S_IRWXUGO ; 
 int S_ISGID ; 
 int S_ISUID ; 
 int S_ISVTX ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUGO ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUGO ; 
 int S_IXUSR ; 
 scalar_t__ scnprintf (char*,size_t,char*,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_mode_t(char *bf, size_t size, struct syscall_arg *arg)
{
	int printed = 0, mode = arg->val;

#define	P_MODE(n) \
	if ((mode & S_##n) == S_##n) { \
		printed += scnprintf(bf + printed, size - printed, "%s%s", printed ? "|" : "", #n); \
		mode &= ~S_##n; \
	}

	P_MODE(IALLUGO);
	P_MODE(IRWXUGO);
	P_MODE(IRUGO);
	P_MODE(IWUGO);
	P_MODE(IXUGO);
	P_MODE(IFMT);
	P_MODE(IFSOCK);
	P_MODE(IFLNK);
	P_MODE(IFREG);
	P_MODE(IFBLK);
	P_MODE(IFDIR);
	P_MODE(IFCHR);
	P_MODE(IFIFO);
	P_MODE(ISUID);
	P_MODE(ISGID);
	P_MODE(ISVTX);
	P_MODE(IRWXU);
	P_MODE(IRUSR);
	P_MODE(IWUSR);
	P_MODE(IXUSR);
	P_MODE(IRWXG);
	P_MODE(IRGRP);
	P_MODE(IWGRP);
	P_MODE(IXGRP);
	P_MODE(IRWXO);
	P_MODE(IROTH);
	P_MODE(IWOTH);
	P_MODE(IXOTH);
#undef P_MODE

	if (mode)
		printed += scnprintf(bf + printed, size - printed, "%s%#x", printed ? "|" : "", mode);

	return printed;
}
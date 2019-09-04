#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char time64_t ;
struct cred {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct coredump_params {TYPE_1__* siginfo; int /*<<< orphan*/  mm_flags; } ;
struct core_name {char* corename; scalar_t__ used; } ;
struct TYPE_10__ {int /*<<< orphan*/  comm; } ;
struct TYPE_9__ {int /*<<< orphan*/  nodename; } ;
struct TYPE_8__ {char si_signo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RLIMIT_CORE ; 
 char __get_dumpable (int /*<<< orphan*/ ) ; 
 int cn_esc_printf (struct core_name*,char*,int /*<<< orphan*/ ) ; 
 int cn_print_exe_file (struct core_name*) ; 
 int cn_printf (struct core_name*,char*,char) ; 
 int /*<<< orphan*/  core_name_size ; 
 char* core_pattern ; 
 scalar_t__ core_uses_pid ; 
 TYPE_3__* current ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ expand_corename (struct core_name*,int /*<<< orphan*/ ) ; 
 char from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 char ktime_get_real_seconds () ; 
 char rlimit (int /*<<< orphan*/ ) ; 
 char task_pid_nr (TYPE_3__*) ; 
 char task_pid_vnr (TYPE_3__*) ; 
 char task_tgid_nr (TYPE_3__*) ; 
 char task_tgid_vnr (TYPE_3__*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uts_sem ; 
 TYPE_2__* utsname () ; 

__attribute__((used)) static int format_corename(struct core_name *cn, struct coredump_params *cprm)
{
	const struct cred *cred = current_cred();
	const char *pat_ptr = core_pattern;
	int ispipe = (*pat_ptr == '|');
	int pid_in_pattern = 0;
	int err = 0;

	cn->used = 0;
	cn->corename = NULL;
	if (expand_corename(cn, core_name_size))
		return -ENOMEM;
	cn->corename[0] = '\0';

	if (ispipe)
		++pat_ptr;

	/* Repeat as long as we have more pattern to process and more output
	   space */
	while (*pat_ptr) {
		if (*pat_ptr != '%') {
			err = cn_printf(cn, "%c", *pat_ptr++);
		} else {
			switch (*++pat_ptr) {
			/* single % at the end, drop that */
			case 0:
				goto out;
			/* Double percent, output one percent */
			case '%':
				err = cn_printf(cn, "%c", '%');
				break;
			/* pid */
			case 'p':
				pid_in_pattern = 1;
				err = cn_printf(cn, "%d",
					      task_tgid_vnr(current));
				break;
			/* global pid */
			case 'P':
				err = cn_printf(cn, "%d",
					      task_tgid_nr(current));
				break;
			case 'i':
				err = cn_printf(cn, "%d",
					      task_pid_vnr(current));
				break;
			case 'I':
				err = cn_printf(cn, "%d",
					      task_pid_nr(current));
				break;
			/* uid */
			case 'u':
				err = cn_printf(cn, "%u",
						from_kuid(&init_user_ns,
							  cred->uid));
				break;
			/* gid */
			case 'g':
				err = cn_printf(cn, "%u",
						from_kgid(&init_user_ns,
							  cred->gid));
				break;
			case 'd':
				err = cn_printf(cn, "%d",
					__get_dumpable(cprm->mm_flags));
				break;
			/* signal that caused the coredump */
			case 's':
				err = cn_printf(cn, "%d",
						cprm->siginfo->si_signo);
				break;
			/* UNIX time of coredump */
			case 't': {
				time64_t time;

				time = ktime_get_real_seconds();
				err = cn_printf(cn, "%lld", time);
				break;
			}
			/* hostname */
			case 'h':
				down_read(&uts_sem);
				err = cn_esc_printf(cn, "%s",
					      utsname()->nodename);
				up_read(&uts_sem);
				break;
			/* executable */
			case 'e':
				err = cn_esc_printf(cn, "%s", current->comm);
				break;
			case 'E':
				err = cn_print_exe_file(cn);
				break;
			/* core limit size */
			case 'c':
				err = cn_printf(cn, "%lu",
					      rlimit(RLIMIT_CORE));
				break;
			default:
				break;
			}
			++pat_ptr;
		}

		if (err)
			return err;
	}

out:
	/* Backward compatibility with core_uses_pid:
	 *
	 * If core_pattern does not include a %p (as is the default)
	 * and core_uses_pid is set, then .%pid will be appended to
	 * the filename. Do not do this for piped commands. */
	if (!ispipe && !pid_in_pattern && core_uses_pid) {
		err = cn_printf(cn, ".%d", task_tgid_vnr(current));
		if (err)
			return err;
	}
	return ispipe;
}
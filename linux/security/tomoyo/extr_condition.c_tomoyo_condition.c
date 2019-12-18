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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct tomoyo_request_info {struct tomoyo_execve* ee; struct tomoyo_obj_info* obj; } ;
struct tomoyo_path_info {int dummy; } ;
struct tomoyo_obj_info {int validate_done; struct tomoyo_mini_stat* stat; int /*<<< orphan*/ * stat_valid; struct tomoyo_path_info* symlink_target; } ;
struct tomoyo_number_union {unsigned long* values; scalar_t__ group; } ;
struct tomoyo_name_union {int dummy; } ;
struct tomoyo_mini_stat {unsigned long ino; unsigned long mode; int /*<<< orphan*/  rdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct tomoyo_execve {struct linux_binprm* bprm; } ;
struct tomoyo_envp {int dummy; } ;
struct tomoyo_condition_element {int equals; int left; int right; } ;
struct tomoyo_condition {int condc; int argc; int envc; int numbers_count; int names_count; } ;
struct tomoyo_argv {int dummy; } ;
struct linux_binprm {unsigned long argc; unsigned long envc; struct file* file; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned long MAJOR (int /*<<< orphan*/ ) ; 
 unsigned long MINOR (int /*<<< orphan*/ ) ; 
 unsigned long S_IALLUGO ; 
 unsigned long S_IFBLK ; 
 unsigned long S_IFCHR ; 
 unsigned long S_IFDIR ; 
 unsigned long S_IFIFO ; 
 unsigned long S_IFLNK ; 
 unsigned long S_IFMT ; 
 unsigned long S_IFREG ; 
 unsigned long S_IFSOCK ; 
 unsigned long S_ISGID ; 
 unsigned long S_ISUID ; 
 unsigned long S_ISVTX ; 
 int const TOMOYO_ARGV_ENTRY ; 
 int const TOMOYO_ENVP_ENTRY ; 
#define  TOMOYO_EXEC_ARGC 187 
#define  TOMOYO_EXEC_ENVC 186 
#define  TOMOYO_EXEC_REALPATH 185 
#define  TOMOYO_MODE_GROUP_EXECUTE 184 
#define  TOMOYO_MODE_GROUP_READ 183 
#define  TOMOYO_MODE_GROUP_WRITE 182 
#define  TOMOYO_MODE_OTHERS_EXECUTE 181 
#define  TOMOYO_MODE_OTHERS_READ 180 
#define  TOMOYO_MODE_OTHERS_WRITE 179 
#define  TOMOYO_MODE_OWNER_EXECUTE 178 
#define  TOMOYO_MODE_OWNER_READ 177 
#define  TOMOYO_MODE_OWNER_WRITE 176 
#define  TOMOYO_MODE_SETGID 175 
#define  TOMOYO_MODE_SETUID 174 
#define  TOMOYO_MODE_STICKY 173 
 int const TOMOYO_NAME_UNION ; 
#define  TOMOYO_NUMBER_UNION 172 
 int TOMOYO_PATH1 ; 
#define  TOMOYO_PATH1_DEV_MAJOR 171 
#define  TOMOYO_PATH1_DEV_MINOR 170 
#define  TOMOYO_PATH1_GID 169 
#define  TOMOYO_PATH1_INO 168 
#define  TOMOYO_PATH1_MAJOR 167 
#define  TOMOYO_PATH1_MINOR 166 
 int TOMOYO_PATH1_PARENT ; 
#define  TOMOYO_PATH1_PARENT_GID 165 
#define  TOMOYO_PATH1_PARENT_INO 164 
#define  TOMOYO_PATH1_PARENT_PERM 163 
#define  TOMOYO_PATH1_PARENT_UID 162 
#define  TOMOYO_PATH1_PERM 161 
#define  TOMOYO_PATH1_TYPE 160 
#define  TOMOYO_PATH1_UID 159 
 int TOMOYO_PATH2 ; 
#define  TOMOYO_PATH2_DEV_MAJOR 158 
#define  TOMOYO_PATH2_DEV_MINOR 157 
#define  TOMOYO_PATH2_GID 156 
#define  TOMOYO_PATH2_INO 155 
#define  TOMOYO_PATH2_MAJOR 154 
#define  TOMOYO_PATH2_MINOR 153 
 int TOMOYO_PATH2_PARENT ; 
#define  TOMOYO_PATH2_PARENT_GID 152 
#define  TOMOYO_PATH2_PARENT_INO 151 
#define  TOMOYO_PATH2_PARENT_PERM 150 
#define  TOMOYO_PATH2_PARENT_UID 149 
#define  TOMOYO_PATH2_PERM 148 
#define  TOMOYO_PATH2_TYPE 147 
#define  TOMOYO_PATH2_UID 146 
#define  TOMOYO_SYMLINK_TARGET 145 
#define  TOMOYO_TASK_EGID 144 
#define  TOMOYO_TASK_EUID 143 
#define  TOMOYO_TASK_FSGID 142 
#define  TOMOYO_TASK_FSUID 141 
#define  TOMOYO_TASK_GID 140 
#define  TOMOYO_TASK_PID 139 
#define  TOMOYO_TASK_PPID 138 
#define  TOMOYO_TASK_SGID 137 
#define  TOMOYO_TASK_SUID 136 
#define  TOMOYO_TASK_UID 135 
#define  TOMOYO_TYPE_IS_BLOCK_DEV 134 
#define  TOMOYO_TYPE_IS_CHAR_DEV 133 
#define  TOMOYO_TYPE_IS_DIRECTORY 132 
#define  TOMOYO_TYPE_IS_FIFO 131 
#define  TOMOYO_TYPE_IS_FILE 130 
#define  TOMOYO_TYPE_IS_SOCKET 129 
#define  TOMOYO_TYPE_IS_SYMLINK 128 
 int /*<<< orphan*/  current_egid () ; 
 int /*<<< orphan*/  current_euid () ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  current_gid () ; 
 int /*<<< orphan*/  current_sgid () ; 
 int /*<<< orphan*/  current_suid () ; 
 int /*<<< orphan*/  current_uid () ; 
 unsigned long from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  tomoyo_compare_name_union (struct tomoyo_path_info*,struct tomoyo_name_union const*) ; 
 int /*<<< orphan*/  tomoyo_get_attributes (struct tomoyo_obj_info*) ; 
 int const tomoyo_number_matches_group (unsigned long,unsigned long,scalar_t__) ; 
 int tomoyo_scan_bprm (struct tomoyo_execve*,int,struct tomoyo_argv const*,int,struct tomoyo_envp const*) ; 
 int /*<<< orphan*/  tomoyo_scan_exec_realpath (struct file*,struct tomoyo_name_union const*,int const) ; 
 unsigned long tomoyo_sys_getpid () ; 
 unsigned long tomoyo_sys_getppid () ; 

bool tomoyo_condition(struct tomoyo_request_info *r,
		      const struct tomoyo_condition *cond)
{
	u32 i;
	unsigned long min_v[2] = { 0, 0 };
	unsigned long max_v[2] = { 0, 0 };
	const struct tomoyo_condition_element *condp;
	const struct tomoyo_number_union *numbers_p;
	const struct tomoyo_name_union *names_p;
	const struct tomoyo_argv *argv;
	const struct tomoyo_envp *envp;
	struct tomoyo_obj_info *obj;
	u16 condc;
	u16 argc;
	u16 envc;
	struct linux_binprm *bprm = NULL;

	if (!cond)
		return true;
	condc = cond->condc;
	argc = cond->argc;
	envc = cond->envc;
	obj = r->obj;
	if (r->ee)
		bprm = r->ee->bprm;
	if (!bprm && (argc || envc))
		return false;
	condp = (struct tomoyo_condition_element *) (cond + 1);
	numbers_p = (const struct tomoyo_number_union *) (condp + condc);
	names_p = (const struct tomoyo_name_union *)
		(numbers_p + cond->numbers_count);
	argv = (const struct tomoyo_argv *) (names_p + cond->names_count);
	envp = (const struct tomoyo_envp *) (argv + argc);
	for (i = 0; i < condc; i++) {
		const bool match = condp->equals;
		const u8 left = condp->left;
		const u8 right = condp->right;
		bool is_bitop[2] = { false, false };
		u8 j;

		condp++;
		/* Check argv[] and envp[] later. */
		if (left == TOMOYO_ARGV_ENTRY || left == TOMOYO_ENVP_ENTRY)
			continue;
		/* Check string expressions. */
		if (right == TOMOYO_NAME_UNION) {
			const struct tomoyo_name_union *ptr = names_p++;
			struct tomoyo_path_info *symlink;
			struct tomoyo_execve *ee;
			struct file *file;

			switch (left) {
			case TOMOYO_SYMLINK_TARGET:
				symlink = obj ? obj->symlink_target : NULL;
				if (!symlink ||
				    !tomoyo_compare_name_union(symlink, ptr)
				    == match)
					goto out;
				break;
			case TOMOYO_EXEC_REALPATH:
				ee = r->ee;
				file = ee ? ee->bprm->file : NULL;
				if (!tomoyo_scan_exec_realpath(file, ptr,
							       match))
					goto out;
				break;
			}
			continue;
		}
		/* Check numeric or bit-op expressions. */
		for (j = 0; j < 2; j++) {
			const u8 index = j ? right : left;
			unsigned long value = 0;

			switch (index) {
			case TOMOYO_TASK_UID:
				value = from_kuid(&init_user_ns, current_uid());
				break;
			case TOMOYO_TASK_EUID:
				value = from_kuid(&init_user_ns, current_euid());
				break;
			case TOMOYO_TASK_SUID:
				value = from_kuid(&init_user_ns, current_suid());
				break;
			case TOMOYO_TASK_FSUID:
				value = from_kuid(&init_user_ns, current_fsuid());
				break;
			case TOMOYO_TASK_GID:
				value = from_kgid(&init_user_ns, current_gid());
				break;
			case TOMOYO_TASK_EGID:
				value = from_kgid(&init_user_ns, current_egid());
				break;
			case TOMOYO_TASK_SGID:
				value = from_kgid(&init_user_ns, current_sgid());
				break;
			case TOMOYO_TASK_FSGID:
				value = from_kgid(&init_user_ns, current_fsgid());
				break;
			case TOMOYO_TASK_PID:
				value = tomoyo_sys_getpid();
				break;
			case TOMOYO_TASK_PPID:
				value = tomoyo_sys_getppid();
				break;
			case TOMOYO_TYPE_IS_SOCKET:
				value = S_IFSOCK;
				break;
			case TOMOYO_TYPE_IS_SYMLINK:
				value = S_IFLNK;
				break;
			case TOMOYO_TYPE_IS_FILE:
				value = S_IFREG;
				break;
			case TOMOYO_TYPE_IS_BLOCK_DEV:
				value = S_IFBLK;
				break;
			case TOMOYO_TYPE_IS_DIRECTORY:
				value = S_IFDIR;
				break;
			case TOMOYO_TYPE_IS_CHAR_DEV:
				value = S_IFCHR;
				break;
			case TOMOYO_TYPE_IS_FIFO:
				value = S_IFIFO;
				break;
			case TOMOYO_MODE_SETUID:
				value = S_ISUID;
				break;
			case TOMOYO_MODE_SETGID:
				value = S_ISGID;
				break;
			case TOMOYO_MODE_STICKY:
				value = S_ISVTX;
				break;
			case TOMOYO_MODE_OWNER_READ:
				value = 0400;
				break;
			case TOMOYO_MODE_OWNER_WRITE:
				value = 0200;
				break;
			case TOMOYO_MODE_OWNER_EXECUTE:
				value = 0100;
				break;
			case TOMOYO_MODE_GROUP_READ:
				value = 0040;
				break;
			case TOMOYO_MODE_GROUP_WRITE:
				value = 0020;
				break;
			case TOMOYO_MODE_GROUP_EXECUTE:
				value = 0010;
				break;
			case TOMOYO_MODE_OTHERS_READ:
				value = 0004;
				break;
			case TOMOYO_MODE_OTHERS_WRITE:
				value = 0002;
				break;
			case TOMOYO_MODE_OTHERS_EXECUTE:
				value = 0001;
				break;
			case TOMOYO_EXEC_ARGC:
				if (!bprm)
					goto out;
				value = bprm->argc;
				break;
			case TOMOYO_EXEC_ENVC:
				if (!bprm)
					goto out;
				value = bprm->envc;
				break;
			case TOMOYO_NUMBER_UNION:
				/* Fetch values later. */
				break;
			default:
				if (!obj)
					goto out;
				if (!obj->validate_done) {
					tomoyo_get_attributes(obj);
					obj->validate_done = true;
				}
				{
					u8 stat_index;
					struct tomoyo_mini_stat *stat;

					switch (index) {
					case TOMOYO_PATH1_UID:
					case TOMOYO_PATH1_GID:
					case TOMOYO_PATH1_INO:
					case TOMOYO_PATH1_MAJOR:
					case TOMOYO_PATH1_MINOR:
					case TOMOYO_PATH1_TYPE:
					case TOMOYO_PATH1_DEV_MAJOR:
					case TOMOYO_PATH1_DEV_MINOR:
					case TOMOYO_PATH1_PERM:
						stat_index = TOMOYO_PATH1;
						break;
					case TOMOYO_PATH2_UID:
					case TOMOYO_PATH2_GID:
					case TOMOYO_PATH2_INO:
					case TOMOYO_PATH2_MAJOR:
					case TOMOYO_PATH2_MINOR:
					case TOMOYO_PATH2_TYPE:
					case TOMOYO_PATH2_DEV_MAJOR:
					case TOMOYO_PATH2_DEV_MINOR:
					case TOMOYO_PATH2_PERM:
						stat_index = TOMOYO_PATH2;
						break;
					case TOMOYO_PATH1_PARENT_UID:
					case TOMOYO_PATH1_PARENT_GID:
					case TOMOYO_PATH1_PARENT_INO:
					case TOMOYO_PATH1_PARENT_PERM:
						stat_index =
							TOMOYO_PATH1_PARENT;
						break;
					case TOMOYO_PATH2_PARENT_UID:
					case TOMOYO_PATH2_PARENT_GID:
					case TOMOYO_PATH2_PARENT_INO:
					case TOMOYO_PATH2_PARENT_PERM:
						stat_index =
							TOMOYO_PATH2_PARENT;
						break;
					default:
						goto out;
					}
					if (!obj->stat_valid[stat_index])
						goto out;
					stat = &obj->stat[stat_index];
					switch (index) {
					case TOMOYO_PATH1_UID:
					case TOMOYO_PATH2_UID:
					case TOMOYO_PATH1_PARENT_UID:
					case TOMOYO_PATH2_PARENT_UID:
						value = from_kuid(&init_user_ns, stat->uid);
						break;
					case TOMOYO_PATH1_GID:
					case TOMOYO_PATH2_GID:
					case TOMOYO_PATH1_PARENT_GID:
					case TOMOYO_PATH2_PARENT_GID:
						value = from_kgid(&init_user_ns, stat->gid);
						break;
					case TOMOYO_PATH1_INO:
					case TOMOYO_PATH2_INO:
					case TOMOYO_PATH1_PARENT_INO:
					case TOMOYO_PATH2_PARENT_INO:
						value = stat->ino;
						break;
					case TOMOYO_PATH1_MAJOR:
					case TOMOYO_PATH2_MAJOR:
						value = MAJOR(stat->dev);
						break;
					case TOMOYO_PATH1_MINOR:
					case TOMOYO_PATH2_MINOR:
						value = MINOR(stat->dev);
						break;
					case TOMOYO_PATH1_TYPE:
					case TOMOYO_PATH2_TYPE:
						value = stat->mode & S_IFMT;
						break;
					case TOMOYO_PATH1_DEV_MAJOR:
					case TOMOYO_PATH2_DEV_MAJOR:
						value = MAJOR(stat->rdev);
						break;
					case TOMOYO_PATH1_DEV_MINOR:
					case TOMOYO_PATH2_DEV_MINOR:
						value = MINOR(stat->rdev);
						break;
					case TOMOYO_PATH1_PERM:
					case TOMOYO_PATH2_PERM:
					case TOMOYO_PATH1_PARENT_PERM:
					case TOMOYO_PATH2_PARENT_PERM:
						value = stat->mode & S_IALLUGO;
						break;
					}
				}
				break;
			}
			max_v[j] = value;
			min_v[j] = value;
			switch (index) {
			case TOMOYO_MODE_SETUID:
			case TOMOYO_MODE_SETGID:
			case TOMOYO_MODE_STICKY:
			case TOMOYO_MODE_OWNER_READ:
			case TOMOYO_MODE_OWNER_WRITE:
			case TOMOYO_MODE_OWNER_EXECUTE:
			case TOMOYO_MODE_GROUP_READ:
			case TOMOYO_MODE_GROUP_WRITE:
			case TOMOYO_MODE_GROUP_EXECUTE:
			case TOMOYO_MODE_OTHERS_READ:
			case TOMOYO_MODE_OTHERS_WRITE:
			case TOMOYO_MODE_OTHERS_EXECUTE:
				is_bitop[j] = true;
			}
		}
		if (left == TOMOYO_NUMBER_UNION) {
			/* Fetch values now. */
			const struct tomoyo_number_union *ptr = numbers_p++;

			min_v[0] = ptr->values[0];
			max_v[0] = ptr->values[1];
		}
		if (right == TOMOYO_NUMBER_UNION) {
			/* Fetch values now. */
			const struct tomoyo_number_union *ptr = numbers_p++;

			if (ptr->group) {
				if (tomoyo_number_matches_group(min_v[0],
								max_v[0],
								ptr->group)
				    == match)
					continue;
			} else {
				if ((min_v[0] <= ptr->values[1] &&
				     max_v[0] >= ptr->values[0]) == match)
					continue;
			}
			goto out;
		}
		/*
		 * Bit operation is valid only when counterpart value
		 * represents permission.
		 */
		if (is_bitop[0] && is_bitop[1]) {
			goto out;
		} else if (is_bitop[0]) {
			switch (right) {
			case TOMOYO_PATH1_PERM:
			case TOMOYO_PATH1_PARENT_PERM:
			case TOMOYO_PATH2_PERM:
			case TOMOYO_PATH2_PARENT_PERM:
				if (!(max_v[0] & max_v[1]) == !match)
					continue;
			}
			goto out;
		} else if (is_bitop[1]) {
			switch (left) {
			case TOMOYO_PATH1_PERM:
			case TOMOYO_PATH1_PARENT_PERM:
			case TOMOYO_PATH2_PERM:
			case TOMOYO_PATH2_PARENT_PERM:
				if (!(max_v[0] & max_v[1]) == !match)
					continue;
			}
			goto out;
		}
		/* Normal value range comparison. */
		if ((min_v[0] <= max_v[1] && max_v[0] >= min_v[1]) == match)
			continue;
out:
		return false;
	}
	/* Check argv[] and envp[] now. */
	if (r->ee && (argc || envc))
		return tomoyo_scan_bprm(r->ee, argc, argv, envc, envp);
	return true;
}
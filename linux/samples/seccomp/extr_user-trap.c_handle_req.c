#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  target ;
struct seccomp_notif_resp {int /*<<< orphan*/  error; scalar_t__ val; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {scalar_t__ nr; int* args; } ;
struct seccomp_notif {int pid; TYPE_1__ data; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  source ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int MS_BIND ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SECCOMP_IOCTL_NOTIF_ID_VALID ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ __NR_mount ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ lseek (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mount (char*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int handle_req(struct seccomp_notif *req,
		      struct seccomp_notif_resp *resp, int listener)
{
	char path[PATH_MAX], source[PATH_MAX], target[PATH_MAX];
	int ret = -1, mem;

	resp->id = req->id;
	resp->error = -EPERM;
	resp->val = 0;

	if (req->data.nr != __NR_mount) {
		fprintf(stderr, "huh? trapped something besides mount? %d\n", req->data.nr);
		return -1;
	}

	/* Only allow bind mounts. */
	if (!(req->data.args[3] & MS_BIND))
		return 0;

	/*
	 * Ok, let's read the task's memory to see where they wanted their
	 * mount to go.
	 */
	snprintf(path, sizeof(path), "/proc/%d/mem", req->pid);
	mem = open(path, O_RDONLY);
	if (mem < 0) {
		perror("open mem");
		return -1;
	}

	/*
	 * Now we avoid a TOCTOU: we referred to a pid by its pid, but since
	 * the pid that made the syscall may have died, we need to confirm that
	 * the pid is still valid after we open its /proc/pid/mem file. We can
	 * ask the listener fd this as follows.
	 *
	 * Note that this check should occur *after* any task-specific
	 * resources are opened, to make sure that the task has not died and
	 * we're not wrongly reading someone else's state in order to make
	 * decisions.
	 */
	if (ioctl(listener, SECCOMP_IOCTL_NOTIF_ID_VALID, &req->id) < 0) {
		fprintf(stderr, "task died before we could map its memory\n");
		goto out;
	}

	/*
	 * Phew, we've got the right /proc/pid/mem. Now we can read it. Note
	 * that to avoid another TOCTOU, we should read all of the pointer args
	 * before we decide to allow the syscall.
	 */
	if (lseek(mem, req->data.args[0], SEEK_SET) < 0) {
		perror("seek");
		goto out;
	}

	ret = read(mem, source, sizeof(source));
	if (ret < 0) {
		perror("read");
		goto out;
	}

	if (lseek(mem, req->data.args[1], SEEK_SET) < 0) {
		perror("seek");
		goto out;
	}

	ret = read(mem, target, sizeof(target));
	if (ret < 0) {
		perror("read");
		goto out;
	}

	/*
	 * Our policy is to only allow bind mounts inside /tmp. This isn't very
	 * interesting, because we could do unprivlieged bind mounts with user
	 * namespaces already, but you get the idea.
	 */
	if (!strncmp(source, "/tmp/", 5) && !strncmp(target, "/tmp/", 5)) {
		if (mount(source, target, NULL, req->data.args[3], NULL) < 0) {
			ret = -1;
			perror("actual mount");
			goto out;
		}
		resp->error = 0;
	}

	/* Even if we didn't allow it because of policy, generating the
	 * response was be a success, because we want to tell the worker EPERM.
	 */
	ret = 0;

out:
	close(mem);
	return ret;
}
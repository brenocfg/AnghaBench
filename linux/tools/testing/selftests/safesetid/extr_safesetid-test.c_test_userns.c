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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  map_file_name ;

/* Variables and functions */
 int CLONE_NEWUSER ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  SYS_clone ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ snprintf (char*,size_t,char*,int) ; 
 int syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int write_file (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool test_userns(bool expect_success)
{
	uid_t uid;
	char map_file_name[32];
	size_t sz = sizeof(map_file_name);
	pid_t cpid;
	bool success;

	uid = getuid();

	int clone_flags = CLONE_NEWUSER;
	cpid = syscall(SYS_clone, clone_flags, NULL);
	if (cpid == -1) {
	    printf("clone failed");
	    return false;
	}

	if (cpid == 0) {	/* Code executed by child */
		// Give parent 1 second to write map file
		sleep(1);
		exit(EXIT_SUCCESS);
	} else {		/* Code executed by parent */
		if(snprintf(map_file_name, sz, "/proc/%d/uid_map", cpid) < 0) {
			printf("preparing file name string failed");
			return false;
		}
		success = write_file(map_file_name, "0 0 1", uid);
		return success == expect_success;
	}

	printf("should not reach here");
	return false;
}
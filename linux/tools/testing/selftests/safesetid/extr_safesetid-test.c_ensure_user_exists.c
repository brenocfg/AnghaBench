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
typedef  int uid_t ;
struct passwd {char* pw_name; int pw_uid; char* pw_gecos; char* pw_dir; char* pw_shell; } ;
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getpwuid (int) ; 
 int /*<<< orphan*/  memset (struct passwd*,int,int) ; 
 int putpwent (struct passwd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void ensure_user_exists(uid_t uid)
{
	struct passwd p;

	FILE *fd;
	char name_str[10];

	if (getpwuid(uid) == NULL) {
		memset(&p,0x00,sizeof(p));
		fd=fopen("/etc/passwd","a");
		if (fd == NULL)
			die("couldn't open file\n");
		if (fseek(fd, 0, SEEK_END))
			die("couldn't fseek\n");
		snprintf(name_str, 10, "%d", uid);
		p.pw_name=name_str;
		p.pw_uid=uid;
		p.pw_gecos="Test account";
		p.pw_dir="/dev/null";
		p.pw_shell="/bin/false";
		int value = putpwent(&p,fd);
		if (value != 0)
			die("putpwent failed\n");
		if (fclose(fd))
			die("fclose failed\n");
	}
}
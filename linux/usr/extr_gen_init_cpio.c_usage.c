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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(const char *prog)
{
	fprintf(stderr, "Usage:\n"
		"\t%s [-t <timestamp>] <cpio_list>\n"
		"\n"
		"<cpio_list> is a file containing newline separated entries that\n"
		"describe the files to be included in the initramfs archive:\n"
		"\n"
		"# a comment\n"
		"file <name> <location> <mode> <uid> <gid> [<hard links>]\n"
		"dir <name> <mode> <uid> <gid>\n"
		"nod <name> <mode> <uid> <gid> <dev_type> <maj> <min>\n"
		"slink <name> <target> <mode> <uid> <gid>\n"
		"pipe <name> <mode> <uid> <gid>\n"
		"sock <name> <mode> <uid> <gid>\n"
		"\n"
		"<name>       name of the file/dir/nod/etc in the archive\n"
		"<location>   location of the file in the current filesystem\n"
		"             expands shell variables quoted with ${}\n"
		"<target>     link target\n"
		"<mode>       mode/permissions of the file\n"
		"<uid>        user id (0=root)\n"
		"<gid>        group id (0=root)\n"
		"<dev_type>   device type (b=block, c=character)\n"
		"<maj>        major number of nod\n"
		"<min>        minor number of nod\n"
		"<hard links> space separated list of other links to file\n"
		"\n"
		"example:\n"
		"# A simple initramfs\n"
		"dir /dev 0755 0 0\n"
		"nod /dev/console 0600 0 0 c 5 1\n"
		"dir /root 0700 0 0\n"
		"dir /sbin 0755 0 0\n"
		"file /sbin/kinit /usr/src/klibc/kinit/kinit 0755 0 0\n"
		"\n"
		"<timestamp> is time in seconds since Epoch that will be used\n"
		"as mtime for symlinks, special files and directories. The default\n"
		"is to use the current time for these entries.\n",
		prog);
}
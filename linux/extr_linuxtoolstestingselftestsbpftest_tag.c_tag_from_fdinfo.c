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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getpid () ; 
 int hex2bin (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 scalar_t__ strncmp (char*,char*,int const) ; 

__attribute__((used)) static void tag_from_fdinfo(int fd_prog, uint8_t *tag, uint32_t len)
{
	const int prefix_len = sizeof("prog_tag:\t") - 1;
	char buff[256];
	int ret = -1;
	FILE *fp;

	snprintf(buff, sizeof(buff), "/proc/%d/fdinfo/%d", getpid(),
		 fd_prog);
	fp = fopen(buff, "r");
	assert(fp);

	while (fgets(buff, sizeof(buff), fp)) {
		if (strncmp(buff, "prog_tag:\t", prefix_len))
			continue;
		ret = hex2bin(tag, buff + prefix_len, len);
		break;
	}

	fclose(fp);
	assert(!ret);
}
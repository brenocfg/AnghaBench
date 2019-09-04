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
struct mic_info {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  close (int) ; 
 char* errno ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpsslog (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  munmap (char*,scalar_t__) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsysfs (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void
set_log_buf_info(struct mic_info *mic)
{
	int fd;
	off_t len;
	char system_map[] = "/lib/firmware/mic/System.map";
	char *map, *temp, log_buf[17] = {'\0'};

	fd = open(system_map, O_RDONLY);
	if (fd < 0) {
		mpsslog("%s: Opening System.map failed: %d\n",
			mic->name, errno);
		return;
	}
	len = lseek(fd, 0, SEEK_END);
	if (len < 0) {
		mpsslog("%s: Reading System.map size failed: %d\n",
			mic->name, errno);
		close(fd);
		return;
	}
	map = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED) {
		mpsslog("%s: mmap of System.map failed: %d\n",
			mic->name, errno);
		close(fd);
		return;
	}
	temp = strstr(map, "__log_buf");
	if (!temp) {
		mpsslog("%s: __log_buf not found: %d\n", mic->name, errno);
		munmap(map, len);
		close(fd);
		return;
	}
	strncpy(log_buf, temp - 19, 16);
	setsysfs(mic->name, "log_buf_addr", log_buf);
	mpsslog("%s: log_buf_addr: %s\n", mic->name, log_buf);
	temp = strstr(map, "log_buf_len");
	if (!temp) {
		mpsslog("%s: log_buf_len not found: %d\n", mic->name, errno);
		munmap(map, len);
		close(fd);
		return;
	}
	strncpy(log_buf, temp - 19, 16);
	setsysfs(mic->name, "log_buf_len", log_buf);
	mpsslog("%s: log_buf_len: %s\n", mic->name, log_buf);
	munmap(map, len);
	close(fd);
}
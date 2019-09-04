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
struct stat {int st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 char* malloc (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static char *read_file(char *file_name, int *size)
{
	struct stat st;
	char *buf;
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0) {
		perror(file_name);
		return NULL;
	}
	if (fstat(fd, &st)) {
		perror("Could not determine file size");
		close(fd);
		return NULL;
	}
	*size = st.st_size;
	buf = malloc(*size);
	if (!buf) {
		perror("Allocating memory failed");
		close(fd);
		return NULL;
	}
	if (read(fd, buf, *size) != *size) {
		perror("File read failed");
		close(fd);
		return NULL;
	}
	close(fd);
	return buf;
}
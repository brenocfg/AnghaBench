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
struct vdso_file {int found; char* temp_file_name; int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDSO__MAP_NAME ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ find_map (void**,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* memdup (void*,size_t) ; 
 int mkstemp (char*) ; 
 scalar_t__ write (int,char*,size_t) ; 

__attribute__((used)) static char *get_file(struct vdso_file *vdso_file)
{
	char *vdso = NULL;
	char *buf = NULL;
	void *start, *end;
	size_t size;
	int fd;

	if (vdso_file->found)
		return vdso_file->temp_file_name;

	if (vdso_file->error || find_map(&start, &end, VDSO__MAP_NAME))
		return NULL;

	size = end - start;

	buf = memdup(start, size);
	if (!buf)
		return NULL;

	fd = mkstemp(vdso_file->temp_file_name);
	if (fd < 0)
		goto out;

	if (size == (size_t) write(fd, buf, size))
		vdso = vdso_file->temp_file_name;

	close(fd);

 out:
	free(buf);

	vdso_file->found = (vdso != NULL);
	vdso_file->error = !vdso_file->found;
	return vdso;
}
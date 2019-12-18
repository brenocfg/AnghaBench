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
typedef  int /*<<< orphan*/  uint16_t ;
struct jitheader {int /*<<< orphan*/  elf_mach; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,...) ; 

__attribute__((used)) static int get_e_machine(struct jitheader *hdr)
{
	ssize_t sret;
	char id[16];
	int fd, ret = -1;
	struct {
		uint16_t e_type;
		uint16_t e_machine;
	} info;

	fd = open("/proc/self/exe", O_RDONLY);
	if (fd == -1)
		return -1;

	sret = read(fd, id, sizeof(id));
	if (sret != sizeof(id))
		goto error;

	/* check ELF signature */
	if (id[0] != 0x7f || id[1] != 'E' || id[2] != 'L' || id[3] != 'F')
		goto error;

	sret = read(fd, &info, sizeof(info));
	if (sret != sizeof(info))
		goto error;

	hdr->elf_mach = info.e_machine;
	ret = 0;
error:
	close(fd);
	return ret;
}
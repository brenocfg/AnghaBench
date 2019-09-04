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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int MCPU ; 
 int /*<<< orphan*/  MSR_FIDVID_STATUS ; 
 int MSR_S_HI_CURRENT_VID ; 
 int MSR_S_LO_CURRENT_FID ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,int*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int get_fidvid(uint32_t cpu, uint32_t *fid, uint32_t *vid)
{
	int err = 1;
	uint64_t msr = 0;
	int fd;
	char file[20];

	if (cpu > MCPU)
		goto out;

	sprintf(file, "/dev/cpu/%d/msr", cpu);

	fd = open(file, O_RDONLY);
	if (fd < 0)
		goto out;
	lseek(fd, MSR_FIDVID_STATUS, SEEK_CUR);
	if (read(fd, &msr, 8) != 8)
		goto err1;

	*fid = ((uint32_t )(msr & 0xffffffffull)) & MSR_S_LO_CURRENT_FID;
	*vid = ((uint32_t )(msr>>32 & 0xffffffffull)) & MSR_S_HI_CURRENT_VID;
	err = 0;
err1:
	close(fd);
out:
	return err;
}
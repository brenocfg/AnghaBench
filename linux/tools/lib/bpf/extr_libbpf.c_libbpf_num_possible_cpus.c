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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 int read (int,char*,int) ; 
 int sscanf (char*,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  strerror (int) ; 

int libbpf_num_possible_cpus(void)
{
	static const char *fcpu = "/sys/devices/system/cpu/possible";
	int len = 0, n = 0, il = 0, ir = 0;
	unsigned int start = 0, end = 0;
	int tmp_cpus = 0;
	static int cpus;
	char buf[128];
	int error = 0;
	int fd = -1;

	tmp_cpus = READ_ONCE(cpus);
	if (tmp_cpus > 0)
		return tmp_cpus;

	fd = open(fcpu, O_RDONLY);
	if (fd < 0) {
		error = errno;
		pr_warning("Failed to open file %s: %s\n",
			   fcpu, strerror(error));
		return -error;
	}
	len = read(fd, buf, sizeof(buf));
	close(fd);
	if (len <= 0) {
		error = len ? errno : EINVAL;
		pr_warning("Failed to read # of possible cpus from %s: %s\n",
			   fcpu, strerror(error));
		return -error;
	}
	if (len == sizeof(buf)) {
		pr_warning("File %s size overflow\n", fcpu);
		return -EOVERFLOW;
	}
	buf[len] = '\0';

	for (ir = 0, tmp_cpus = 0; ir <= len; ir++) {
		/* Each sub string separated by ',' has format \d+-\d+ or \d+ */
		if (buf[ir] == ',' || buf[ir] == '\0') {
			buf[ir] = '\0';
			n = sscanf(&buf[il], "%u-%u", &start, &end);
			if (n <= 0) {
				pr_warning("Failed to get # CPUs from %s\n",
					   &buf[il]);
				return -EINVAL;
			} else if (n == 1) {
				end = start;
			}
			tmp_cpus += end - start + 1;
			il = ir + 1;
		}
	}
	if (tmp_cpus <= 0) {
		pr_warning("Invalid #CPUs %d from %s\n", tmp_cpus, fcpu);
		return -EINVAL;
	}

	WRITE_ONCE(cpus, tmp_cpus);
	return tmp_cpus;
}
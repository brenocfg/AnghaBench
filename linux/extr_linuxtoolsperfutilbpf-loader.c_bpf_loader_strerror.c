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
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 size_t ERRNO_OFFSET (int) ; 
 int STRERR_BUFSIZE ; 
 int __BPF_LOADER_ERRNO__END ; 
 int __BPF_LOADER_ERRNO__START ; 
 int __LIBBPF_ERRNO__START ; 
 char** bpf_loader_strerror_table ; 
 int libbpf_strerror (int,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 
 char* str_error_r (int,char*,int) ; 

__attribute__((used)) static int
bpf_loader_strerror(int err, char *buf, size_t size)
{
	char sbuf[STRERR_BUFSIZE];
	const char *msg;

	if (!buf || !size)
		return -1;

	err = err > 0 ? err : -err;

	if (err >= __LIBBPF_ERRNO__START)
		return libbpf_strerror(err, buf, size);

	if (err >= __BPF_LOADER_ERRNO__START && err < __BPF_LOADER_ERRNO__END) {
		msg = bpf_loader_strerror_table[ERRNO_OFFSET(err)];
		snprintf(buf, size, "%s", msg);
		buf[size - 1] = '\0';
		return 0;
	}

	if (err >= __BPF_LOADER_ERRNO__END)
		snprintf(buf, size, "Unknown bpf loader error %d", err);
	else
		snprintf(buf, size, "%s",
			 str_error_r(err, sbuf, sizeof(sbuf)));

	buf[size - 1] = '\0';
	return -1;
}
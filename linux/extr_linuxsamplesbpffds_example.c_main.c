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
typedef  int uint32_t ;

/* Variables and functions */
 int BPF_F_GET ; 
 int BPF_F_KEY ; 
 int BPF_F_PIN ; 
 int BPF_F_PIN_GET ; 
 int BPF_F_VAL ; 
#define  BPF_M_MAP 129 
#define  BPF_M_PROG 128 
 int BPF_M_UNSPEC ; 
 int bpf_do_map (char const*,int,int,int) ; 
 int bpf_do_prog (char const*,int,char const*) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
	const char *file = NULL, *object = NULL;
	uint32_t key = 0, value = 0, flags = 0;
	int opt, mode = BPF_M_UNSPEC;

	while ((opt = getopt(argc, argv, "F:PGmk:v:po:")) != -1) {
		switch (opt) {
		/* General args */
		case 'F':
			file = optarg;
			break;
		case 'P':
			flags |= BPF_F_PIN;
			break;
		case 'G':
			flags |= BPF_F_GET;
			break;
		/* Map-related args */
		case 'm':
			mode = BPF_M_MAP;
			break;
		case 'k':
			key = strtoul(optarg, NULL, 0);
			flags |= BPF_F_KEY;
			break;
		case 'v':
			value = strtoul(optarg, NULL, 0);
			flags |= BPF_F_VAL;
			break;
		/* Prog-related args */
		case 'p':
			mode = BPF_M_PROG;
			break;
		case 'o':
			object = optarg;
			break;
		default:
			goto out;
		}
	}

	if (!(flags & BPF_F_PIN_GET) || !file)
		goto out;

	switch (mode) {
	case BPF_M_MAP:
		return bpf_do_map(file, flags, key, value);
	case BPF_M_PROG:
		return bpf_do_prog(file, flags, object);
	}
out:
	usage();
	return -1;
}
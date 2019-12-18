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
typedef  int u32 ;
typedef  int /*<<< orphan*/  testir2 ;
typedef  int /*<<< orphan*/  testir1 ;
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
struct input_event {scalar_t__ type; scalar_t__ code; int value; } ;
struct bpf_object {int dummy; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_LIRC_MODE2 ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_LIRC_MODE2 ; 
 scalar_t__ ENOENT ; 
 scalar_t__ EV_MSC ; 
 scalar_t__ EV_REL ; 
 scalar_t__ MSC_SCAN ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  POLLIN ; 
 scalar_t__ REL_Y ; 
 int bpf_prog_attach (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bpf_prog_detach2 (int,int,int /*<<< orphan*/ ) ; 
 int bpf_prog_load (char*,int /*<<< orphan*/ ,struct bpf_object**,int*) ; 
 int bpf_prog_query (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 scalar_t__ errno ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,struct input_event*,int) ; 
 int write (int,int*,int) ; 

int main(int argc, char **argv)
{
	struct bpf_object *obj;
	int ret, lircfd, progfd, inputfd;
	int testir1 = 0x1dead;
	int testir2 = 0x20101;
	u32 prog_ids[10], prog_flags[10], prog_cnt;

	if (argc != 3) {
		printf("Usage: %s /dev/lircN /dev/input/eventM\n", argv[0]);
		return 2;
	}

	ret = bpf_prog_load("test_lirc_mode2_kern.o",
			    BPF_PROG_TYPE_LIRC_MODE2, &obj, &progfd);
	if (ret) {
		printf("Failed to load bpf program\n");
		return 1;
	}

	lircfd = open(argv[1], O_RDWR | O_NONBLOCK);
	if (lircfd == -1) {
		printf("failed to open lirc device %s: %m\n", argv[1]);
		return 1;
	}

	/* Let's try detach it before it was ever attached */
	ret = bpf_prog_detach2(progfd, lircfd, BPF_LIRC_MODE2);
	if (ret != -1 || errno != ENOENT) {
		printf("bpf_prog_detach2 not attached should fail: %m\n");
		return 1;
	}

	inputfd = open(argv[2], O_RDONLY | O_NONBLOCK);
	if (inputfd == -1) {
		printf("failed to open input device %s: %m\n", argv[1]);
		return 1;
	}

	prog_cnt = 10;
	ret = bpf_prog_query(lircfd, BPF_LIRC_MODE2, 0, prog_flags, prog_ids,
			     &prog_cnt);
	if (ret) {
		printf("Failed to query bpf programs on lirc device: %m\n");
		return 1;
	}

	if (prog_cnt != 0) {
		printf("Expected nothing to be attached\n");
		return 1;
	}

	ret = bpf_prog_attach(progfd, lircfd, BPF_LIRC_MODE2, 0);
	if (ret) {
		printf("Failed to attach bpf to lirc device: %m\n");
		return 1;
	}

	/* Write raw IR */
	ret = write(lircfd, &testir1, sizeof(testir1));
	if (ret != sizeof(testir1)) {
		printf("Failed to send test IR message: %m\n");
		return 1;
	}

	struct pollfd pfd = { .fd = inputfd, .events = POLLIN };
	struct input_event event;

	for (;;) {
		poll(&pfd, 1, 100);

		/* Read decoded IR */
		ret = read(inputfd, &event, sizeof(event));
		if (ret != sizeof(event)) {
			printf("Failed to read decoded IR: %m\n");
			return 1;
		}

		if (event.type == EV_MSC && event.code == MSC_SCAN &&
		    event.value == 0xdead) {
			break;
		}
	}

	/* Write raw IR */
	ret = write(lircfd, &testir2, sizeof(testir2));
	if (ret != sizeof(testir2)) {
		printf("Failed to send test IR message: %m\n");
		return 1;
	}

	for (;;) {
		poll(&pfd, 1, 100);

		/* Read decoded IR */
		ret = read(inputfd, &event, sizeof(event));
		if (ret != sizeof(event)) {
			printf("Failed to read decoded IR: %m\n");
			return 1;
		}

		if (event.type == EV_REL && event.code == REL_Y &&
		    event.value == 1 ) {
			break;
		}
	}

	prog_cnt = 10;
	ret = bpf_prog_query(lircfd, BPF_LIRC_MODE2, 0, prog_flags, prog_ids,
			     &prog_cnt);
	if (ret) {
		printf("Failed to query bpf programs on lirc device: %m\n");
		return 1;
	}

	if (prog_cnt != 1) {
		printf("Expected one program to be attached\n");
		return 1;
	}

	/* Let's try detaching it now it is actually attached */
	ret = bpf_prog_detach2(progfd, lircfd, BPF_LIRC_MODE2);
	if (ret) {
		printf("bpf_prog_detach2: returned %m\n");
		return 1;
	}

	return 0;
}
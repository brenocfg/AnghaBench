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

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 void* atol (char*) ; 
 int /*<<< orphan*/  atoll (char*) ; 
 void** loop_cnt ; 
 void* loop_cnt_1 ; 
 void* loop_cnt_2 ; 
 void* loop_cnt_3 ; 
 void* loop_cnt_4 ; 
 void* loop_cnt_5 ; 
 void* loop_cnt_6 ; 
 void* opt_disable_mod ; 
 int opt_disable_rseq ; 
 int opt_mb ; 
 void* opt_modulo ; 
 int /*<<< orphan*/  opt_reps ; 
 int opt_signal ; 
 void* opt_sleep ; 
 int opt_test ; 
 void* opt_threads ; 
 int opt_yield ; 
 int /*<<< orphan*/  printf_verbose (char*) ; 
 scalar_t__ rseq_register_current_thread () ; 
 scalar_t__ rseq_unregister_current_thread () ; 
 scalar_t__ set_signal_handler () ; 
 int /*<<< orphan*/  show_usage (int,char**) ; 
 int /*<<< orphan*/  test_percpu_buffer () ; 
 int /*<<< orphan*/  test_percpu_inc () ; 
 int /*<<< orphan*/  test_percpu_list () ; 
 int /*<<< orphan*/  test_percpu_memcpy_buffer () ; 
 int /*<<< orphan*/  test_percpu_spinlock () ; 
 int verbose ; 

int main(int argc, char **argv)
{
	int i;

	for (i = 1; i < argc; i++) {
		if (argv[i][0] != '-')
			continue;
		switch (argv[i][1]) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (argc < i + 2) {
				show_usage(argc, argv);
				goto error;
			}
			loop_cnt[argv[i][1] - '0'] = atol(argv[i + 1]);
			i++;
			break;
		case 'm':
			if (argc < i + 2) {
				show_usage(argc, argv);
				goto error;
			}
			opt_modulo = atol(argv[i + 1]);
			if (opt_modulo < 0) {
				show_usage(argc, argv);
				goto error;
			}
			i++;
			break;
		case 's':
			if (argc < i + 2) {
				show_usage(argc, argv);
				goto error;
			}
			opt_sleep = atol(argv[i + 1]);
			if (opt_sleep < 0) {
				show_usage(argc, argv);
				goto error;
			}
			i++;
			break;
		case 'y':
			opt_yield = 1;
			break;
		case 'k':
			opt_signal = 1;
			break;
		case 'd':
			opt_disable_rseq = 1;
			break;
		case 'D':
			if (argc < i + 2) {
				show_usage(argc, argv);
				goto error;
			}
			opt_disable_mod = atol(argv[i + 1]);
			if (opt_disable_mod < 0) {
				show_usage(argc, argv);
				goto error;
			}
			i++;
			break;
		case 't':
			if (argc < i + 2) {
				show_usage(argc, argv);
				goto error;
			}
			opt_threads = atol(argv[i + 1]);
			if (opt_threads < 0) {
				show_usage(argc, argv);
				goto error;
			}
			i++;
			break;
		case 'r':
			if (argc < i + 2) {
				show_usage(argc, argv);
				goto error;
			}
			opt_reps = atoll(argv[i + 1]);
			if (opt_reps < 0) {
				show_usage(argc, argv);
				goto error;
			}
			i++;
			break;
		case 'h':
			show_usage(argc, argv);
			goto end;
		case 'T':
			if (argc < i + 2) {
				show_usage(argc, argv);
				goto error;
			}
			opt_test = *argv[i + 1];
			switch (opt_test) {
			case 's':
			case 'l':
			case 'i':
			case 'b':
			case 'm':
				break;
			default:
				show_usage(argc, argv);
				goto error;
			}
			i++;
			break;
		case 'v':
			verbose = 1;
			break;
		case 'M':
			opt_mb = 1;
			break;
		default:
			show_usage(argc, argv);
			goto error;
		}
	}

	loop_cnt_1 = loop_cnt[1];
	loop_cnt_2 = loop_cnt[2];
	loop_cnt_3 = loop_cnt[3];
	loop_cnt_4 = loop_cnt[4];
	loop_cnt_5 = loop_cnt[5];
	loop_cnt_6 = loop_cnt[6];

	if (set_signal_handler())
		goto error;

	if (!opt_disable_rseq && rseq_register_current_thread())
		goto error;
	switch (opt_test) {
	case 's':
		printf_verbose("spinlock\n");
		test_percpu_spinlock();
		break;
	case 'l':
		printf_verbose("linked list\n");
		test_percpu_list();
		break;
	case 'b':
		printf_verbose("buffer\n");
		test_percpu_buffer();
		break;
	case 'm':
		printf_verbose("memcpy buffer\n");
		test_percpu_memcpy_buffer();
		break;
	case 'i':
		printf_verbose("counter increment\n");
		test_percpu_inc();
		break;
	}
	if (!opt_disable_rseq && rseq_unregister_current_thread())
		abort();
end:
	return 0;

error:
	return -1;
}
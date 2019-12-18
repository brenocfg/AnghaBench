#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  test_file ;
struct TYPE_2__ {int /*<<< orphan*/ * ctx; } ;
struct btf_dump_test_case {char* name; TYPE_1__ opts; } ;
struct btf {int dummy; } ;
typedef  int /*<<< orphan*/  out_file ;
typedef  int /*<<< orphan*/  diff_cmd ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CHECK (int,char*,...) ; 
 int /*<<< orphan*/  IS_ERR (struct btf*) ; 
 int PTR_ERR (struct btf*) ; 
 int /*<<< orphan*/  R_OK ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf__free (struct btf*) ; 
 struct btf* btf__parse_elf (char*,int /*<<< orphan*/ *) ; 
 int btf_dump_all_types (struct btf*,TYPE_1__*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int system (char*) ; 

int test_btf_dump_case(int n, struct btf_dump_test_case *test_case)
{
	char test_file[256], out_file[256], diff_cmd[1024];
	struct btf *btf = NULL;
	int err = 0, fd = -1;
	FILE *f = NULL;

	fprintf(stderr, "Test case #%d (%s): ", n, test_case->name);

	snprintf(test_file, sizeof(test_file), "%s.o", test_case->name);

	btf = btf__parse_elf(test_file, NULL);
	if (CHECK(IS_ERR(btf),
	    "failed to load test BTF: %ld\n", PTR_ERR(btf))) {
		err = -PTR_ERR(btf);
		btf = NULL;
		goto done;
	}

	snprintf(out_file, sizeof(out_file),
		 "/tmp/%s.output.XXXXXX", test_case->name);
	fd = mkstemp(out_file);
	if (CHECK(fd < 0, "failed to create temp output file: %d\n", fd)) {
		err = fd;
		goto done;
	}
	f = fdopen(fd, "w");
	if (CHECK(f == NULL, "failed to open temp output file: %s(%d)\n",
		  strerror(errno), errno)) {
		close(fd);
		goto done;
	}

	test_case->opts.ctx = f;
	err = btf_dump_all_types(btf, &test_case->opts);
	fclose(f);
	close(fd);
	if (CHECK(err, "failure during C dumping: %d\n", err)) {
		goto done;
	}

	snprintf(test_file, sizeof(test_file), "progs/%s.c", test_case->name);
	if (access(test_file, R_OK) == -1)
		/*
		 * When the test is run with O=, kselftest copies TEST_FILES
		 * without preserving the directory structure.
		 */
		snprintf(test_file, sizeof(test_file), "%s.c",
			test_case->name);
	/*
	 * Diff test output and expected test output, contained between
	 * START-EXPECTED-OUTPUT and END-EXPECTED-OUTPUT lines in test case.
	 * For expected output lines, everything before '*' is stripped out.
	 * Also lines containing comment start and comment end markers are
	 * ignored. 
	 */
	snprintf(diff_cmd, sizeof(diff_cmd),
		 "awk '/START-EXPECTED-OUTPUT/{out=1;next} "
		 "/END-EXPECTED-OUTPUT/{out=0} "
		 "/\\/\\*|\\*\\//{next} " /* ignore comment start/end lines */
		 "out {sub(/^[ \\t]*\\*/, \"\"); print}' '%s' | diff -u - '%s'",
		 test_file, out_file);
	err = system(diff_cmd);
	if (CHECK(err,
		  "differing test output, output=%s, err=%d, diff cmd:\n%s\n",
		  out_file, err, diff_cmd))
		goto done;

	remove(out_file);
	fprintf(stderr, "OK\n");

done:
	btf__free(btf);
	return err;
}
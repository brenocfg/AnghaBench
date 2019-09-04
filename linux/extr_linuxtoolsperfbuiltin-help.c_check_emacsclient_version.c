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
struct strbuf {scalar_t__ buf; } ;
struct child_process {char const** argv; int err; int stdout_to_stderr; } ;
typedef  int /*<<< orphan*/  ec_process ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int atoi (scalar_t__) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  finish_command (struct child_process*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct child_process*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strbuf_read (struct strbuf*,int,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strstarts (scalar_t__,char*) ; 

__attribute__((used)) static int check_emacsclient_version(void)
{
	struct strbuf buffer = STRBUF_INIT;
	struct child_process ec_process;
	const char *argv_ec[] = { "emacsclient", "--version", NULL };
	int version;
	int ret = -1;

	/* emacsclient prints its version number on stderr */
	memset(&ec_process, 0, sizeof(ec_process));
	ec_process.argv = argv_ec;
	ec_process.err = -1;
	ec_process.stdout_to_stderr = 1;
	if (start_command(&ec_process)) {
		fprintf(stderr, "Failed to start emacsclient.\n");
		return -1;
	}
	if (strbuf_read(&buffer, ec_process.err, 20) < 0) {
		fprintf(stderr, "Failed to read emacsclient version\n");
		goto out;
	}
	close(ec_process.err);

	/*
	 * Don't bother checking return value, because "emacsclient --version"
	 * seems to always exits with code 1.
	 */
	finish_command(&ec_process);

	if (!strstarts(buffer.buf, "emacsclient")) {
		fprintf(stderr, "Failed to parse emacsclient version.\n");
		goto out;
	}

	version = atoi(buffer.buf + strlen("emacsclient"));

	if (version < 22) {
		fprintf(stderr,
			"emacsclient version '%d' too old (< 22).\n",
			version);
	} else
		ret = 0;
out:
	strbuf_release(&buffer);
	return ret;
}
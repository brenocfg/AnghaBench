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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fwrite (void*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hex_print (void*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  p_err (char*,char const*,...) ; 
 int /*<<< orphan*/  print_data_json (void*,unsigned int) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
print_run_output(void *data, unsigned int size, const char *fname,
		 const char *json_key)
{
	size_t nb_written;
	FILE *f;

	if (!fname)
		return 0;

	if (!strcmp(fname, "-")) {
		f = stdout;
		if (json_output) {
			jsonw_name(json_wtr, json_key);
			print_data_json(data, size);
		} else {
			hex_print(data, size, f);
		}
		return 0;
	}

	f = fopen(fname, "w");
	if (!f) {
		p_err("failed to open %s: %s", fname, strerror(errno));
		return -1;
	}

	nb_written = fwrite(data, 1, size, f);
	fclose(f);
	if (nb_written != size) {
		p_err("failed to write output data/ctx: %s", strerror(errno));
		return -1;
	}

	return 0;
}
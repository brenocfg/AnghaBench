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
struct cal_entry {int id; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int Z_OK ; 
 int be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fread (struct cal_entry*,int,int,int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ get_num (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ htobe16 (scalar_t__) ; 
 int inf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  zerr (int) ; 

int main(int argc, char **argv)
{
	struct cal_entry cal = { .len = 0 };
	FILE *in = stdin;
	FILE *out = stdout;
	size_t limit = 0, skip = 0;
	int initial_offset = 0;
	int entry = -1;
	int ret;
	int opt;

	while ((opt = getopt(argc, argv, "s:e:o:l:i:")) != -1) {
		switch (opt) {
		case 's':
			initial_offset = (int)get_num(optarg);
			if (errno) {
				perror("Failed to parse seek offset");
				goto out_bad;
			}
			break;
		case 'e':
			entry = (int) htobe16(get_num(optarg));
			if (errno) {
				perror("Failed to entry id");
				goto out_bad;
			}
			break;
		case 'o':
			out = fopen(optarg, "w");
			if (!out) {
				perror("Failed to create output file");
				goto out_bad;
			}
			break;
		case 'l':
			limit = (size_t)get_num(optarg);
			if (errno) {
				perror("Failed to parse limit");
				goto out_bad;
			}
			break;
		case 'i':
			skip = (size_t)get_num(optarg);
			if (errno) {
				perror("Failed to parse skip");
				goto out_bad;
			}
			break;
		default: /* '?' */
			usage();
		}
	}

	if (entry == -1)
		usage();

	if (argc > 1 && optind <= argc) {
		in = fopen(argv[optind], "r");
		if (!in) {
			perror("Failed to create output file");
			goto out_bad;
		}
	}

	if (initial_offset) {
		ret = fseek(in, initial_offset, SEEK_CUR);
		if (ret) {
			perror("Failed to seek to calibration table");
			goto out_bad;
		}
	}

	do {
		ret = fseek(in, be16toh(cal.len), SEEK_CUR);
		if (feof(in)) {
			fprintf(stderr, "Reached end of file, but didn't find the matching entry\n");
			goto out_bad;
		} else if (ferror(in)) {
			perror("Failure during seek");
			goto out_bad;
		}

		ret = fread(&cal, 1, sizeof cal, in);
		if (ret != sizeof cal)
			goto out_bad;
	} while (entry != cal.id || cal.id == 0xffff);

	if (cal.id == 0xffff) {
		fprintf(stderr, "Reached end of filesystem, but didn't find the matching entry\n");
		goto out_bad;
	}

	ret = inf(in, out, limit, skip);
	if (ret == Z_OK)
		goto out;

	zerr(ret);

out_bad:
	ret = EXIT_FAILURE;

out:
	fclose(in);
	fclose(out);
	return ret;
}
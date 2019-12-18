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
typedef  int /*<<< orphan*/  hex_pattern ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 char* default_pattern ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,size_t,int,int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 int is_hex_pattern ; 
 void* optarg ; 
 int optind ; 
 scalar_t__ sscanf (char const*,char*,unsigned int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  usage () ; 
 int xor_data (char*,size_t,char const*,int,int) ; 

int main(int argc, char **argv)
{
	char buf[1024];	/* keep this at 1k or adjust garbage calc below */
	FILE *in = stdin;
	FILE *out = stdout;
	char *ifn = NULL;
	char *ofn = NULL;
	const char *pattern = default_pattern;
	char hex_pattern[128];
	unsigned int hex_buf;
	int c;
	int v0, v1, v2;
	size_t n;
	int p_len, p_off = 0;

	while ((c = getopt(argc, argv, "i:o:p:xh")) != -1) {
		switch (c) {
			case 'i':
				ifn = optarg;
				break;
			case 'o':
				ofn = optarg;
				break;
			case 'p':
				pattern = optarg;
				break;
			case 'x':
				is_hex_pattern = true;
				break;
			case 'h':
			default:
				usage();
		}
	}

	if (optind != argc || optind == 1) {
		fprintf(stderr, "illegal arg \"%s\"\n", argv[optind]);
		usage();
	}

	if (ifn && !(in = fopen(ifn, "r"))) {
		fprintf(stderr, "can not open \"%s\" for reading\n", ifn);
		usage();
	}

	if (ofn && !(out = fopen(ofn, "w"))) {
		fprintf(stderr, "can not open \"%s\" for writing\n", ofn);
		usage();
	}

	p_len = strlen(pattern);

	if (p_len == 0) {
		fprintf(stderr, "pattern cannot be empty\n");
		usage();
	}

	if (is_hex_pattern) {
		int i;

		if ((p_len / 2) > sizeof(hex_pattern)) {
			fprintf(stderr, "provided hex pattern is too long\n");
			usage();
		}

		if (p_len % 2 != 0) {
			fprintf(stderr, "the number of characters (hex) is incorrect\n");
			usage();
		}

		for (i = 0; i < (p_len / 2); i++) {
			if (sscanf(pattern + (i * 2), "%2x", &hex_buf) < 0) {
				fprintf(stderr, "invalid hex digit around %d\n", i * 2);
				usage();
			}
			hex_pattern[i] = (char)hex_buf;
		}
	}

	while ((n = fread(buf, 1, sizeof(buf), in)) > 0) {
		if (n < sizeof(buf)) {
			if (ferror(in)) {
			FREAD_ERROR:
				fprintf(stderr, "fread error\n");
				return EXIT_FAILURE;
			}
		}

		if (is_hex_pattern) {
			p_off = xor_data(buf, n, hex_pattern, (p_len / 2),
					 p_off);
		} else {
			p_off = xor_data(buf, n, pattern, p_len, p_off);
		}

		if (!fwrite(buf, n, 1, out)) {
		FWRITE_ERROR:
			fprintf(stderr, "fwrite error\n");
			return EXIT_FAILURE;
		}
	}

	if (ferror(in)) {
		goto FREAD_ERROR;
	}

	if (fflush(out)) {
		goto FWRITE_ERROR;
	}

	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}
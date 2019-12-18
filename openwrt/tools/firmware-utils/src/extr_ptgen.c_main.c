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
typedef  int uint32_t ;
struct TYPE_2__ {char type; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int active ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gen_ptable (int,int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ heads ; 
 int ignore_null_sized_partition ; 
 int kb_align ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 TYPE_1__* parts ; 
 scalar_t__ sectors ; 
 int /*<<< orphan*/  stderr ; 
 int strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  to_kbytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 
 int /*<<< orphan*/  verbose ; 

int main (int argc, char **argv)
{
	char type = 0x83;
	int ch;
	int part = 0;
	uint32_t signature = 0x5452574F; /* 'OWRT' */

	while ((ch = getopt(argc, argv, "h:s:p:a:t:o:vnl:S:")) != -1) {
		switch (ch) {
		case 'o':
			filename = optarg;
			break;
		case 'v':
			verbose++;
			break;
		case 'n':
			ignore_null_sized_partition = true;
			break;
		case 'h':
			heads = (int)strtoul(optarg, NULL, 0);
			break;
		case 's':
			sectors = (int)strtoul(optarg, NULL, 0);
			break;
		case 'p':
			if (part > 3) {
				fprintf(stderr, "Too many partitions\n");
				exit(EXIT_FAILURE);
			}
			parts[part].size = to_kbytes(optarg);
			parts[part++].type = type;
			break;
		case 't':
			type = (char)strtoul(optarg, NULL, 16);
			break;
		case 'a':
			active = (int)strtoul(optarg, NULL, 0);
			if ((active < 0) || (active > 4))
				active = 0;
			break;
		case 'l':
			kb_align = (int)strtoul(optarg, NULL, 0) * 2;
			break;
		case 'S':
			signature = strtoul(optarg, NULL, 0);
			break;
		case '?':
		default:
			usage(argv[0]);
		}
	}
	argc -= optind;
	if (argc || (heads <= 0) || (sectors <= 0) || !filename)
		usage(argv[0]);

	return gen_ptable(signature, part) ? EXIT_FAILURE : EXIT_SUCCESS;
}
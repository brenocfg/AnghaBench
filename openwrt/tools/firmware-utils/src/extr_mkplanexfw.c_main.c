#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  char uchar ;
struct stat {int st_size; } ;
struct planex_hdr {int /*<<< orphan*/  sha1sum; int /*<<< orphan*/  version; int /*<<< orphan*/ * unk1; void* datalen; } ;
typedef  int /*<<< orphan*/  sha1_context ;
typedef  int /*<<< orphan*/  seed ;
struct TYPE_3__ {int datalen; int seed; int /*<<< orphan*/ * unk; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ERRS (char*,int /*<<< orphan*/ *) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 void* HOST_TO_BE32 (int) ; 
 int /*<<< orphan*/  basename (char*) ; 
 TYPE_1__* board ; 
 int /*<<< orphan*/ * board_id ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 TYPE_1__* find_board (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * ifname ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/ * ofname ; 
 void* optarg ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  sha1_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha1_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha1_update (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int stat (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (int) ; 
 char* version ; 

int main(int argc, char *argv[])
{
	int res = EXIT_FAILURE;
	int buflen;
	int err;
	struct stat st;
	char *buf;
	struct planex_hdr *hdr;
	sha1_context ctx;
	uint32_t seed;

	FILE *outfile, *infile;

	progname = basename(argv[0]);

	while ( 1 ) {
		int c;

		c = getopt(argc, argv, "B:i:o:v:h");
		if (c == -1)
			break;

		switch (c) {
		case 'B':
			board_id = optarg;
			break;
		case 'i':
			ifname = optarg;
			break;
		case 'o':
			ofname = optarg;
			break;
		case 'v':
			version = optarg;
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}
	}

	if (board_id == NULL) {
		ERR("no board specified");
		goto err;
	}

	board = find_board(board_id);
	if (board == NULL) {
		ERR("unknown board '%s'", board_id);
		goto err;
	};

	if (ifname == NULL) {
		ERR("no input file specified");
		goto err;
	}

	if (ofname == NULL) {
		ERR("no output file specified");
		goto err;
	}

	err = stat(ifname, &st);
	if (err){
		ERRS("stat failed on %s", ifname);
		goto err;
	}

	if (st.st_size > board->datalen) {
		ERR("file '%s' is too big - max size: 0x%08X (exceeds %lu bytes)\n",
		    ifname, board->datalen, st.st_size - board->datalen);
		goto err;
	}

	buflen = board->datalen + 0x10000;
	buf = malloc(buflen);
	if (!buf) {
		ERR("no memory for buffer\n");
		goto err;
	}

	memset(buf, 0xff, buflen);
	hdr = (struct planex_hdr *)buf;

	hdr->datalen = HOST_TO_BE32(board->datalen);
	hdr->unk1[0] = board->unk[0];
	hdr->unk1[1] = board->unk[1];

	snprintf(hdr->version, sizeof(hdr->version), "%s", version);

	infile = fopen(ifname, "r");
	if (infile == NULL) {
		ERRS("could not open \"%s\" for reading", ifname);
		goto err_free;
	}

	errno = 0;
	fread(buf +  sizeof(*hdr), st.st_size, 1, infile);
	if (errno != 0) {
		ERRS("unable to read from file %s", ifname);
		goto err_close_in;
	}

	seed = HOST_TO_BE32(board->seed);
	sha1_starts(&ctx);
	sha1_update(&ctx, (uchar *) &seed, sizeof(seed));
	sha1_update(&ctx, buf + sizeof(*hdr), board->datalen);
	sha1_finish(&ctx, hdr->sha1sum);

	outfile = fopen(ofname, "w");
	if (outfile == NULL) {
		ERRS("could not open \"%s\" for writing", ofname);
		goto err_close_in;
	}

	errno = 0;
	fwrite(buf, buflen, 1, outfile);
	if (errno) {
		ERRS("unable to write to file %s", ofname);
		goto err_close_out;
	}

	res = EXIT_SUCCESS;

 out_flush:
	fflush(outfile);

 err_close_out:
	fclose(outfile);
	if (res != EXIT_SUCCESS) {
		unlink(ofname);
	}

 err_close_in:
	fclose(infile);

 err_free:
	free(buf);

 err:
	return res;
}
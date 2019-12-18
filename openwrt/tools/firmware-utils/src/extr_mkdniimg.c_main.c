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
typedef  char uint8_t ;
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DNI_HDR_LEN ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ERRS (char*,int /*<<< orphan*/ *) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  basename (char*) ; 
 char* board_id ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 char* hd_id ; 
 int /*<<< orphan*/ * ifname ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ofname ; 
 void* optarg ; 
 int /*<<< orphan*/  progname ; 
 char* region ; 
 int snprintf (char*,int,char*,char*,...) ; 
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
	int pos, rem, i;
	uint8_t csum;

	FILE *outfile, *infile;

	progname = basename(argv[0]);

	while ( 1 ) {
		int c;

		c = getopt(argc, argv, "B:i:o:v:r:H:h");
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
		case 'r':
			region = optarg;
			break;
		case 'H':
			hd_id = optarg;
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

	buflen = st.st_size + DNI_HDR_LEN + 1;
	buf = malloc(buflen);
	if (!buf) {
		ERR("no memory for buffer\n");
		goto err;
	}

	memset(buf, 0, DNI_HDR_LEN);
	pos = snprintf(buf, DNI_HDR_LEN, "device:%s\nversion:V%s\nregion:%s\n",
		       board_id, version, region);
	rem = DNI_HDR_LEN - pos;
	if (pos >= 0 && rem > 1 && hd_id) {
		snprintf(buf + pos, rem, "hd_id:%s\n", hd_id);
	}

	infile = fopen(ifname, "r");
	if (infile == NULL) {
		ERRS("could not open \"%s\" for reading", ifname);
		goto err_free;
	}

	errno = 0;
	fread(buf +  DNI_HDR_LEN, st.st_size, 1, infile);
	if (errno != 0) {
		ERRS("unable to read from file %s", ifname);
		goto err_close_in;
	}

	csum = 0;
	for (i = 0; i < (st.st_size + DNI_HDR_LEN); i++)
		csum += buf[i];

	csum = 0xff - csum;
	buf[st.st_size + DNI_HDR_LEN] = csum;

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
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
struct wrg_header {int /*<<< orphan*/  offset; int /*<<< orphan*/  size; int /*<<< orphan*/  magic2; int /*<<< orphan*/  magic1; int /*<<< orphan*/  devname; int /*<<< orphan*/  signature; } ;
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ERRS (char*,int /*<<< orphan*/ *) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int WRG_MAGIC ; 
 int /*<<< orphan*/  basename (char*) ; 
 int big_endian ; 
 int /*<<< orphan*/ * dev_name ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_digest (struct wrg_header*,char*,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * ifname ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (struct wrg_header*,char,int) ; 
 int offset ; 
 int /*<<< orphan*/ * ofname ; 
 void* optarg ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  put_u32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * signature ; 
 int stat (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int strtoul (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (int) ; 

int main(int argc, char *argv[])
{
	struct wrg_header *header;
	char *buf;
	struct stat st;
	int buflen;
	int err;
	int res = EXIT_FAILURE;

	FILE *outfile, *infile;

	progname = basename(argv[0]);

	while ( 1 ) {
		int c;

		c = getopt(argc, argv, "bd:i:o:s:O:h");
		if (c == -1)
			break;

		switch (c) {
		case 'b':
			big_endian = 1;
			break;
		case 'd':
			dev_name = optarg;
			break;
		case 'i':
			ifname = optarg;
			break;
		case 'o':
			ofname = optarg;
			break;
		case 's':
			signature = optarg;
			break;
		case 'O':
			offset = strtoul(optarg, NULL, 0);
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;

		default:
			usage(EXIT_FAILURE);
			break;
		}
	}

	if (signature == NULL) {
		ERR("no signature specified");
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

	if (dev_name == NULL) {
		ERR("no device name specified");
		goto err;
	}

	err = stat(ifname, &st);
	if (err){
		ERRS("stat failed on %s", ifname);
		goto err;
	}

	buflen = st.st_size + sizeof(struct wrg_header);
	buf = malloc(buflen);
	if (!buf) {
		ERR("no memory for buffer\n");
		goto err;
	}

	infile = fopen(ifname, "r");
	if (infile == NULL) {
		ERRS("could not open \"%s\" for reading", ifname);
		goto err_free;
	}

	errno = 0;
	fread(buf + sizeof(struct wrg_header), st.st_size, 1, infile);
	if (errno != 0) {
		ERRS("unable to read from file %s", ifname);
		goto close_in;
	}

	header = (struct wrg_header *) buf;
	memset(header, '\0', sizeof(struct wrg_header));

	strncpy(header->signature, signature, sizeof(header->signature));
	strncpy(header->devname, dev_name, sizeof(header->signature));
	put_u32(&header->magic1, WRG_MAGIC);
	put_u32(&header->magic2, WRG_MAGIC);
	put_u32(&header->size, st.st_size);
	put_u32(&header->offset, offset);

	get_digest(header, buf + sizeof(struct wrg_header), st.st_size);

	outfile = fopen(ofname, "w");
	if (outfile == NULL) {
		ERRS("could not open \"%s\" for writing", ofname);
		goto close_in;
	}

	errno = 0;
	fwrite(buf, buflen, 1, outfile);
	if (errno) {
		ERRS("unable to write to file %s", ofname);
		goto close_out;
	}

	fflush(outfile);

	res = EXIT_SUCCESS;

close_out:
	fclose(outfile);
	if (res != EXIT_SUCCESS)
		unlink(ofname);
close_in:
	fclose(infile);
err_free:
	free(buf);
err:
	return res;
}
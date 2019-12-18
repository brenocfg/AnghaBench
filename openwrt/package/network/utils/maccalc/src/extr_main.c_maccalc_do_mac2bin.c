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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  mac ;

/* Variables and functions */
 int ERR_INVALID ; 
 int ERR_IO ; 
 int MAC_ADDRESS_LEN ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int parse_mac (char const*,unsigned char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 
 int write (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int maccalc_do_mac2bin(int argc, const char *argv[])
{
	unsigned char mac[MAC_ADDRESS_LEN];
	ssize_t c;
	int err;

	if (argc != 1) {
		usage();
		return ERR_INVALID;
	}

	err = parse_mac(argv[0], mac);
	if (err)
		return err;

	c = write(STDOUT_FILENO, mac, sizeof(mac));
	if (c != sizeof(mac)) {
		fprintf(stderr, "failed to write to stdout\n");
		return ERR_IO;
	}

	return 0;
}
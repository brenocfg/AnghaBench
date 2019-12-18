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
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_mac (unsigned char*) ; 
 int read_safe (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int maccalc_do_bin2mac(int argc, const char *argv[])
{
	unsigned char mac[MAC_ADDRESS_LEN];
	ssize_t c;

	if (argc != 0) {
		usage();
		return ERR_INVALID;
	}

	c = read_safe(STDIN_FILENO, mac, sizeof(mac));
	if (c != sizeof(mac)) {
		fprintf(stderr, "failed to read from stdin\n");
		return ERR_IO;
	}

	print_mac(mac);
	return 0;
}
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
typedef  int uint32_t ;

/* Variables and functions */
 int ERR_INVALID ; 
 int MAC_ADDRESS_LEN ; 
 int atoi (char const*) ; 
 int parse_mac (char const*,unsigned char*) ; 
 int /*<<< orphan*/  print_mac (unsigned char*) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int maccalc_do_add(int argc, const char *argv[])
{
	unsigned char mac[MAC_ADDRESS_LEN];
	uint32_t t;
	int err;
	int i;

	if (argc != 2) {
		usage();
		return ERR_INVALID;
	}

	err = parse_mac(argv[0], mac);
	if (err)
		return err;

	i = atoi(argv[1]);

	t = (mac[3] << 16) | (mac[4] << 8) | mac[5];
	t += i;
	mac[3] = (t >> 16) & 0xff;
	mac[4] = (t >> 8) & 0xff;
	mac[5] = t & 0xff;

	print_mac(mac);
	return 0;
}
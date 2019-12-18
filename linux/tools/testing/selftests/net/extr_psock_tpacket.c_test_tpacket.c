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
struct ring {int dummy; } ;
typedef  int /*<<< orphan*/  ring ;

/* Variables and functions */
 int KSFT_SKIP ; 
 int TPACKET_V1 ; 
 int /*<<< orphan*/  bind_ring (int,struct ring*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct ring*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmap_ring (int,struct ring*) ; 
 int pfsocket (int) ; 
 int /*<<< orphan*/  setup_ring (int,struct ring*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ test_kernel_bit_width () ; 
 scalar_t__ test_user_bit_width () ; 
 char** tpacket_str ; 
 char** type_str ; 
 int /*<<< orphan*/  unmap_ring (int,struct ring*) ; 
 int /*<<< orphan*/  walk_ring (int,struct ring*) ; 

__attribute__((used)) static int test_tpacket(int version, int type)
{
	int sock;
	struct ring ring;

	fprintf(stderr, "test: %s with %s ", tpacket_str[version],
		type_str[type]);
	fflush(stderr);

	if (version == TPACKET_V1 &&
	    test_kernel_bit_width() != test_user_bit_width()) {
		fprintf(stderr, "test: skip %s %s since user and kernel "
			"space have different bit width\n",
			tpacket_str[version], type_str[type]);
		return KSFT_SKIP;
	}

	sock = pfsocket(version);
	memset(&ring, 0, sizeof(ring));
	setup_ring(sock, &ring, version, type);
	mmap_ring(sock, &ring);
	bind_ring(sock, &ring);
	walk_ring(sock, &ring);
	unmap_ring(sock, &ring);
	close(sock);

	fprintf(stderr, "\n");
	return 0;
}
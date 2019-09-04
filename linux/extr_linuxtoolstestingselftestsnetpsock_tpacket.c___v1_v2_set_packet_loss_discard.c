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
typedef  int /*<<< orphan*/  discard ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_LOSS ; 
 int /*<<< orphan*/  SOL_PACKET ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void __v1_v2_set_packet_loss_discard(int sock)
{
	int ret, discard = 1;

	ret = setsockopt(sock, SOL_PACKET, PACKET_LOSS, (void *) &discard,
			 sizeof(discard));
	if (ret == -1) {
		perror("setsockopt");
		exit(1);
	}
}
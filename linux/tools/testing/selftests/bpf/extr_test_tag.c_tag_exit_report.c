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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  tag_dump (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tag_exit_report(int insns, int fd_map, uint8_t *ftag,
			    uint8_t *atag, uint32_t len)
{
	printf("Program tag mismatch for %d insns%s!\n", insns,
	       fd_map < 0 ? "" : " with map");

	tag_dump("  fdinfo result: ", ftag, len);
	tag_dump("  af_alg result: ", atag, len);
	exit(1);
}
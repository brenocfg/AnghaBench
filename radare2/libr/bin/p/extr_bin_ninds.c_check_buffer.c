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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ninlogohead ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int r_buf_read_at (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool check_buffer(RBuffer *b) {
	ut8 ninlogohead[6];
	if (r_buf_read_at (b, 0xc0, ninlogohead, sizeof (ninlogohead)) == 6) {
		/* begin of nintendo logo =    \x24\xff\xae\x51\x69\x9a */
		if (!memcmp (ninlogohead, "\x24\xff\xae\x51\x69\x9a", 6)) {
			return true;
		}
		/* begin of Homebrew magic */
		if (!memcmp (ninlogohead, "\xC8\x60\x4F\xE2\x01\x70", 6)){
			return true;
		}
	}
	return false;
}
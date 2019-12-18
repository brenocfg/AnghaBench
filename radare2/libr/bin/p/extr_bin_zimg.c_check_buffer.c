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
typedef  int /*<<< orphan*/  zimghdr ;
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool check_buffer(RBuffer *b) {
	ut8 zimghdr[8];
	if (r_buf_read_at (b, 0, zimghdr, sizeof (zimghdr))) {
		// Checking ARM zImage kernel
		if (!memcmp (zimghdr, "\x00\x00\xa0\xe1\x00\x00\xa0\xe1", 8)) {
			return true;
		}
	}
	return false;
}
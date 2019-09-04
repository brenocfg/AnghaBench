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
typedef  scalar_t__ ut8 ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  arch ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 scalar_t__ memcmp (scalar_t__*,char*,int) ; 
 int r_buf_read_at (int /*<<< orphan*/ *,int,scalar_t__*,int) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 

__attribute__((used)) static bool check_buffer(RBuffer *buf) {
	if (r_buf_size (buf) < 32) {
		return false;
	}

	ut8 hdr[4];
	ut8 arch[9] = { 0 };
	int rarch = r_buf_read_at (buf, 9, arch, sizeof (arch) - 1);
	int rhdr = r_buf_read_at (buf, 0, hdr, sizeof (hdr));
	if (rhdr != sizeof (hdr) || memcmp (hdr, "dyld", 4)) {
		return false;
	}
	if (rarch > 0 && arch[0] && !strstr ((const char *)arch, "arm64")) {
		return false;
	}
	return true;
}
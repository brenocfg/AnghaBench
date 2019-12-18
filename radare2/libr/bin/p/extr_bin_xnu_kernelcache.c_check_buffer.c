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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int is_kernelcache_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool check_buffer(RBuffer *b) {
	if (r_buf_size (b) > 4) {
		ut8 buf[4];
		r_buf_read_at (b, 0, buf, sizeof (buf));
		if (!memcmp (buf, "\xcf\xfa\xed\xfe", 4)) {
			return is_kernelcache_buffer (b);
		}
	}
	return false;
}
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
typedef  int /*<<< orphan*/  magic ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 scalar_t__ N64_ROM_START ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ r_buf_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool check_buffer(RBuffer *b) {
	ut8 magic[4];
	if (r_buf_size (b) < N64_ROM_START) {
		return false;
	}
	(void)r_buf_read_at (b, 0, magic, sizeof (magic));
	return !memcmp (magic, "\x80\x37\x12\x40", 4);
}
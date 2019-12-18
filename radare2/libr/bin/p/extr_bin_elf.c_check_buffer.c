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
typedef  int ut8 ;
typedef  int /*<<< orphan*/  b ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  ELFMAG ; 
 int /*<<< orphan*/  SELFMAG ; 
 int /*<<< orphan*/  memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static bool check_buffer(RBuffer *buf) {
	ut8 b[5] = {0};
	r_buf_read_at (buf, 0, b, sizeof (b));
	return !memcmp (b, ELFMAG, SELFMAG) && b[4] != 2;
}
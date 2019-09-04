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
struct xdr_buf {unsigned int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCAL_BUF_LEN ; 
 int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rotate_buf_a_little (struct xdr_buf*,int) ; 

__attribute__((used)) static void _rotate_left(struct xdr_buf *buf, unsigned int shift)
{
	int shifted = 0;
	int this_shift;

	shift %= buf->len;
	while (shifted < shift) {
		this_shift = min(shift - shifted, LOCAL_BUF_LEN);
		rotate_buf_a_little(buf, this_shift);
		shifted += this_shift;
	}
}
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
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  R_BUF_SET ; 
 int /*<<< orphan*/  r_buf_read8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_buf_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_newline () ; 
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void showBuffer(RBuffer *b) {
	int i;
	if (b && r_buf_size (b) > 0) {
		r_buf_seek (b, 0, R_BUF_SET);
		for (i = 0; i < r_buf_size (b); i++) {
			r_cons_printf ("%02x", r_buf_read8 (b));
		}
		r_cons_newline ();
	}
}
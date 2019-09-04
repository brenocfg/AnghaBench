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
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int buf_eof ; 
 int buf_err ; 
 int r_buf_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ut8 read_byte(RBuffer *b) {
	ut8 r = 0;
	int length;

	if (buf_eof || buf_err) {
		return 0;
	}
	if ((length = r_buf_read (b, &r, 1)) != 1) {
		if (length == -1) {
			buf_err = true;
		}
		if (length == 0) {
			buf_eof = true;
		}
		return 0;
	}
	return r;
}
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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int check_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_buf_new_with_pointers (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_bytes(const ut8 *buf, ut64 len) {
	RBuffer *b = r_buf_new_with_pointers (buf, len);
	if (b) {
		int res = check_buffer (b);
		r_buf_free (b);
		return res > 0;
	}
	return false;
}
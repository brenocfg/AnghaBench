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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  r_buf_read_le64_at (int /*<<< orphan*/ *,int) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 

ut64 readLE64(RBuffer *buf, int off) {
	return r_buf_size (buf) >= off + 8? r_buf_read_le64_at (buf, off): 0;
}
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
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  UT32_MAX ; 
 scalar_t__ r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_read_be32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline ut32 r_buf_read_be32_at(RBuffer *b, ut64 addr) {
	ut8 buf[sizeof (ut32)];
	int r = (int) r_buf_read_at (b, addr, buf, sizeof (buf));
	return r == sizeof (buf)? r_read_be32 (buf): UT32_MAX;
}
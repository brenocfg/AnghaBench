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
typedef  int /*<<< orphan*/  ut32 ;

/* Variables and functions */
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_write_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ut8 *r_rap_packet(ut8 type, ut32 len) {
	ut8 *buf = malloc (len + 5);
	if (buf) {
		buf[0] = type;
		r_write_be32 (buf + 1, len);
	}
	return buf;
}
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
 int /*<<< orphan*/  R_MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_read_be32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_rap_packet_fill(ut8 *buf, const ut8* src, int len) {
	if (buf && src && len > 0) {
		ut32 curlen = r_read_be32 (buf + 1);
		memcpy (buf + 5, src, R_MIN (curlen, len));
	}
}
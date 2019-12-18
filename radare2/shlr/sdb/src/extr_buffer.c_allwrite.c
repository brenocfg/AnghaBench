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
typedef  scalar_t__ ut32 ;
typedef  scalar_t__ (* BufferOp ) (int,char const*,scalar_t__) ;

/* Variables and functions */

__attribute__((used)) static int allwrite(BufferOp op, int fd, const char *buf, ut32 len) {
	ut32 w;
	while (len > 0) {
		w = op (fd, buf, len);
		if (w != len) {
			return 0;
		}
		buf += w;
		len -= w;
	}
	return 1;
}
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
struct pushpull {char* buf; unsigned int buflen; unsigned int ofs; unsigned int reserve; } ;

/* Variables and functions */

__attribute__((used)) static inline void init_pushpull(struct pushpull *pp, char *buf,
				 unsigned buflen, unsigned ofs,
				 unsigned reserve)
{
	pp->buf = buf;
	pp->buflen = buflen;
	pp->ofs = ofs;
	pp->reserve = reserve;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_5__ {int flags; int nwin; TYPE_1__* win; } ;
typedef  TYPE_2__ cistpl_io_t ;
struct TYPE_4__ {int len; scalar_t__ base; } ;

/* Variables and functions */
 int CISTPL_IO_LINES_MASK ; 

__attribute__((used)) static u_char *parse_io(u_char *p, u_char *q, cistpl_io_t *io)
{
	int i, j, bsz, lsz;

	if (p == q)
		return NULL;
	io->flags = *p;

	if (!(*p & 0x80)) {
		io->nwin = 1;
		io->win[0].base = 0;
		io->win[0].len = (1 << (io->flags & CISTPL_IO_LINES_MASK));
		return p+1;
	}

	if (++p == q)
		return NULL;
	io->nwin = (*p & 0x0f) + 1;
	bsz = (*p & 0x30) >> 4;
	if (bsz == 3)
		bsz++;
	lsz = (*p & 0xc0) >> 6;
	if (lsz == 3)
		lsz++;
	p++;

	for (i = 0; i < io->nwin; i++) {
		io->win[i].base = 0;
		io->win[i].len = 1;
		for (j = 0; j < bsz; j++, p++) {
			if (p == q)
				return NULL;
			io->win[i].base += *p << (j*8);
		}
		for (j = 0; j < lsz; j++, p++) {
			if (p == q)
				return NULL;
			io->win[i].len += *p << (j*8);
		}
	}
	return p;
}
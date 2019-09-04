#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {unsigned int start; unsigned int flags; int end; } ;
struct pcmcia_socket {TYPE_1__* io; } ;
struct TYPE_2__ {unsigned int InUse; struct resource* res; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned int IORESOURCE_BITS ; 
 int MAX_IO_WIN ; 
 struct resource* __iodyn_find_io_region (struct pcmcia_socket*,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ adjust_resource (struct resource*,unsigned int,scalar_t__) ; 
 scalar_t__ resource_size (struct resource*) ; 

__attribute__((used)) static int iodyn_find_io(struct pcmcia_socket *s, unsigned int attr,
			unsigned int *base, unsigned int num,
			unsigned int align, struct resource **parent)
{
	int i, ret = 0;

	/* Check for an already-allocated window that must conflict with
	 * what was asked for.  It is a hack because it does not catch all
	 * potential conflicts, just the most obvious ones.
	 */
	for (i = 0; i < MAX_IO_WIN; i++) {
		if (!s->io[i].res)
			continue;

		if (!*base)
			continue;

		if ((s->io[i].res->start & (align-1)) == *base)
			return -EBUSY;
	}

	for (i = 0; i < MAX_IO_WIN; i++) {
		struct resource *res = s->io[i].res;
		unsigned int try;

		if (res && (res->flags & IORESOURCE_BITS) !=
			(attr & IORESOURCE_BITS))
			continue;

		if (!res) {
			if (align == 0)
				align = 0x10000;

			res = s->io[i].res = __iodyn_find_io_region(s, *base,
								num, align);
			if (!res)
				return -EINVAL;

			*base = res->start;
			s->io[i].res->flags =
				((res->flags & ~IORESOURCE_BITS) |
					(attr & IORESOURCE_BITS));
			s->io[i].InUse = num;
			*parent = res;
			return 0;
		}

		/* Try to extend top of window */
		try = res->end + 1;
		if ((*base == 0) || (*base == try)) {
			if (adjust_resource(s->io[i].res, res->start,
					    resource_size(res) + num))
				continue;
			*base = try;
			s->io[i].InUse += num;
			*parent = res;
			return 0;
		}

		/* Try to extend bottom of window */
		try = res->start - num;
		if ((*base == 0) || (*base == try)) {
			if (adjust_resource(s->io[i].res,
					    res->start - num,
					    resource_size(res) + num))
				continue;
			*base = try;
			s->io[i].InUse += num;
			*parent = res;
			return 0;
		}
	}

	return -EINVAL;
}
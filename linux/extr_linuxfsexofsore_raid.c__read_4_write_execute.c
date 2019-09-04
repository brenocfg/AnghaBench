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
struct ore_io_state {unsigned int numdevs; struct ore_io_state* ios_read_4_write; TYPE_1__* layout; int /*<<< orphan*/  pages; } ;
struct TYPE_2__ {scalar_t__ mirrors_p1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ORE_DBGMSG (char*,int) ; 
 int /*<<< orphan*/  _mark_read4write_pages_uptodate (struct ore_io_state*,int) ; 
 int _ore_read_mirror (struct ore_io_state*,unsigned int) ; 
 int ore_io_execute (struct ore_io_state*) ; 
 int /*<<< orphan*/  ore_put_io_state (struct ore_io_state*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int _read_4_write_execute(struct ore_io_state *ios)
{
	struct ore_io_state *ios_read;
	unsigned i;
	int ret;

	ios_read = ios->ios_read_4_write;
	if (!ios_read)
		return 0;

	/* FIXME: Ugly to signal _sbi_read_mirror that we have bio(s). Change
	 * to check for per_dev->bio
	 */
	ios_read->pages = ios->pages;

	/* Now read these devices */
	for (i = 0; i < ios_read->numdevs; i += ios_read->layout->mirrors_p1) {
		ret = _ore_read_mirror(ios_read, i);
		if (unlikely(ret))
			return ret;
	}

	ret = ore_io_execute(ios_read); /* Synchronus execution */
	if (unlikely(ret)) {
		ORE_DBGMSG("!! ore_io_execute => %d\n", ret);
		return ret;
	}

	_mark_read4write_pages_uptodate(ios_read, ret);
	ore_put_io_state(ios_read);
	ios->ios_read_4_write = NULL; /* Might need a reuse at last stripe */
	return 0;
}
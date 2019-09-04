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
struct page_collect {int read_4_write; } ;
struct page {TYPE_1__* mapping; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_ERR (char*,int) ; 
 int /*<<< orphan*/  _pcol_init (struct page_collect*,int,int /*<<< orphan*/ ) ; 
 int read_exec (struct page_collect*) ; 
 int readpage_strip (struct page_collect*,struct page*) ; 

__attribute__((used)) static int _readpage(struct page *page, bool read_4_write)
{
	struct page_collect pcol;
	int ret;

	_pcol_init(&pcol, 1, page->mapping->host);

	pcol.read_4_write = read_4_write;
	ret = readpage_strip(&pcol, page);
	if (ret) {
		EXOFS_ERR("_readpage => %d\n", ret);
		return ret;
	}

	return read_exec(&pcol);
}
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
struct TYPE_5__ {void (* free ) (void*) ;} ;
struct TYPE_4__ {TYPE_2__* mirrors; } ;
typedef  TYPE_1__ RBinMem ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_free (TYPE_2__*) ; 

__attribute__((used)) static void r_bbin_mem_free(void *data) {
	RBinMem *mem = (RBinMem *)data;
	if (mem && mem->mirrors) {
		mem->mirrors->free = r_bbin_mem_free;
		r_list_free (mem->mirrors);
		mem->mirrors = NULL;
	}
	free (mem);
}
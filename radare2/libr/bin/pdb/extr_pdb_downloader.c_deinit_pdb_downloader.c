#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* symbol_store_path; struct TYPE_5__* user_agent; struct TYPE_5__* symbol_server; struct TYPE_5__* guid; struct TYPE_5__* dbg_file; } ;
struct TYPE_4__ {scalar_t__ download; TYPE_3__* opt; } ;
typedef  TYPE_1__ SPDBDownloader ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (TYPE_3__*) ; 

void deinit_pdb_downloader(SPDBDownloader *pd) {
	R_FREE (pd->opt->dbg_file);
	R_FREE (pd->opt->guid);
	R_FREE (pd->opt->symbol_server);
	R_FREE (pd->opt->user_agent);
	R_FREE (pd->opt->symbol_store_path);
	R_FREE (pd->opt);
	pd->download = 0;
}
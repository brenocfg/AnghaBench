#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  realpath_cache; int /*<<< orphan*/  realpath_cache_ttl; int /*<<< orphan*/  realpath_cache_size_limit; scalar_t__ realpath_cache_size; int /*<<< orphan*/  cwd; } ;
typedef  TYPE_1__ virtual_cwd_globals ;

/* Variables and functions */
 int /*<<< orphan*/  CWD_STATE_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REALPATH_CACHE_SIZE ; 
 int /*<<< orphan*/  REALPATH_CACHE_TTL ; 
 int /*<<< orphan*/  main_cwd_state ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cwd_globals_ctor(virtual_cwd_globals *cwd_g) /* {{{ */
{
	CWD_STATE_COPY(&cwd_g->cwd, &main_cwd_state);
	cwd_g->realpath_cache_size = 0;
	cwd_g->realpath_cache_size_limit = REALPATH_CACHE_SIZE;
	cwd_g->realpath_cache_ttl = REALPATH_CACHE_TTL;
	memset(cwd_g->realpath_cache, 0, sizeof(cwd_g->realpath_cache));
}
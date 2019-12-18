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
struct mg_mgr_init_opts {int dummy; } ;
struct mg_mgr {int dummy; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mg_mgr_init_opts*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_mgr_init_opt (struct mg_mgr*,void*,struct mg_mgr_init_opts) ; 

void mg_mgr_init(struct mg_mgr *m, void *user_data) {
  struct mg_mgr_init_opts opts;
  memset(&opts, 0, sizeof(opts));
  mg_mgr_init_opt(m, user_data, opts);
}
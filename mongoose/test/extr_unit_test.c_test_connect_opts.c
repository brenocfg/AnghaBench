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
struct mg_mgr {int dummy; } ;
struct mg_connection {void* user_data; int flags; } ;
struct mg_connect_opts {int flags; void* user_data; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MG_F_USER_6 ; 
 int MG_F_WANT_READ ; 
 int /*<<< orphan*/  cb6 ; 
 int /*<<< orphan*/  memset (struct mg_connect_opts*,int /*<<< orphan*/ ,int) ; 
 struct mg_connection* mg_connect_opt (struct mg_mgr*,char*,int /*<<< orphan*/ ,struct mg_connect_opts) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *test_connect_opts(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  struct mg_connect_opts opts;

  memset(&opts, 0, sizeof(opts));
  opts.user_data = (void *) 0xdeadbeef;
  opts.flags = MG_F_USER_6;
  opts.flags |= MG_F_WANT_READ; /* Should not be allowed. */

  mg_mgr_init(&mgr, NULL);
  ASSERT((nc = mg_connect_opt(&mgr, "127.0.0.1:33211", cb6, opts)) != NULL);
  ASSERT(nc->user_data == (void *) 0xdeadbeef);
  ASSERT(nc->flags & MG_F_USER_6);
  ASSERT(!(nc->flags & MG_F_WANT_READ));
  /* TODO(rojer): find a way to test this w/o touching nc (already freed).
    poll_mgr(&mgr, 25);
    ASSERT(nc->flags & MG_F_USER_4);
    ASSERT(nc->flags & MG_F_USER_6);
    ASSERT(!(nc->flags & MG_F_WANT_READ));
  */
  mg_mgr_free(&mgr);
  return NULL;
}
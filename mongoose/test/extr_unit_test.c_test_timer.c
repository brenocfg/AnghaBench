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
struct mg_connection {int* user_data; int ev_timer_time; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_EQ (int,int) ; 
 int /*<<< orphan*/  ASSERT_GT (double,double) ; 
 int /*<<< orphan*/  ASSERT_LT (double,double) ; 
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int /*<<< orphan*/  MG_F_CLOSE_IMMEDIATELY ; 
 int /*<<< orphan*/  c_int_eq ; 
 int /*<<< orphan*/  ev_timer_handler ; 
 struct mg_connection* mg_add_sock (struct mg_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int mg_set_timer (struct mg_connection*,int) ; 
 double mg_time () ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,int*,void*) ; 

__attribute__((used)) static const char *test_timer(void) {
  struct mg_mgr m;
  struct mg_connection *c;
  double begin, end;
  int n = 0, i;

  mg_mgr_init(&m, NULL);
  ASSERT((c = mg_add_sock(&m, INVALID_SOCKET, ev_timer_handler)) != NULL);
  c->user_data = &n;

  /* MG_EV_TIMER should not fire - we did not set it up */
  mg_mgr_poll(&m, 1);
  ASSERT_EQ(n, 0);

  /*
   * Now, set it up. Make sure MG_EV_TIMER event fires.
   * Also, it brings forward the poll timeout.
   */
  ASSERT_EQ(mg_set_timer(c, mg_time() + 0.1), 0.0);
  begin = mg_time();
  /*
   * Windows is a bit sloppy about select() timeouts, so it may take
   * a couple iterations for the timer to actually fire.
   */
  for (i = 0; n != 1 && i < 5; i++) {
    mg_mgr_poll(&m, 1000);
  }
  end = mg_time();
  ASSERT_EQ(n, 1);
  ASSERT_LT(end - begin, 0.9);
  ASSERT_GT(end - begin, 0.09);

  /* Make sure that timer is reset - second time it does not fire */
  ASSERT_EQ(c->ev_timer_time, 0.0);
  mg_mgr_poll(&m, 1);
  ASSERT_EQ(n, 1);

  c->flags |= MG_F_CLOSE_IMMEDIATELY;
  mg_mgr_poll(&m, 1);
  ASSERT_EQ(n, 101);

  /* Async resolver codepath */
  n = 0;
  ASSERT((c = mg_connect(&m, "awful.sad:1234", ev_timer_handler)) != NULL);
  c->user_data = &n;
  mg_set_timer(c, 1);
  poll_until(&m, 1, c_int_eq, &n, (void *) 101);
  ASSERT_EQ(n, 101);

  mg_mgr_free(&m);

  return NULL;
}
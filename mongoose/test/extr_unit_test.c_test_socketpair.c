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
typedef  int /*<<< orphan*/  sock_t ;
typedef  int /*<<< orphan*/  foo ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASSERT_STREQ (char*,char*) ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_socketpair (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *test_socketpair(void) {
  sock_t sp[2];
  static const char foo[] = "hi there";
  char buf[20];

  ASSERT_EQ(mg_socketpair(sp, SOCK_DGRAM), 1);
  ASSERT(sizeof(foo) < sizeof(buf));

  /* Send string in one direction */
  ASSERT_EQ(send(sp[0], foo, sizeof(foo), 0), sizeof(foo));
  ASSERT_EQ(recv(sp[1], buf, sizeof(buf), 0), sizeof(foo));
  ASSERT_STREQ(buf, "hi there");

  /* Now in opposite direction */
  ASSERT_EQ(send(sp[1], foo, sizeof(foo), 0), sizeof(foo));
  ASSERT_EQ(recv(sp[0], buf, sizeof(buf), 0), sizeof(foo));
  ASSERT_STREQ(buf, "hi there");

  closesocket(sp[0]);
  closesocket(sp[1]);

  return NULL;
}
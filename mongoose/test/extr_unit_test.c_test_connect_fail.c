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
struct mg_connection {char* user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  c_str_ne ; 
 int /*<<< orphan*/  cb5 ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,char*,void*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static const char *test_connect_fail(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  char buf[100] = "0";

  mg_mgr_init(&mgr, NULL);
  ASSERT((nc = mg_connect(&mgr, "127.0.0.1:33211", cb5)) != NULL);
  nc->user_data = buf;
  poll_until(&mgr, 1, c_str_ne, buf, (void *) "0");
  mg_mgr_free(&mgr);

/* printf("failed connect status: [%s]\n", buf); */
/* TODO(lsm): fix this for Win32 */
#ifndef _WIN32
  ASSERT(strcmp(buf, "0") != 0);
#endif

  return NULL;
}
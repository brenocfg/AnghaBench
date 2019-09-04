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
struct mg_connection {int dummy; } ;
struct mg_connect_opts {char const** error_string; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_STREQ (char const*,char*) ; 
 int /*<<< orphan*/  cb6 ; 
 int /*<<< orphan*/  memset (struct mg_connect_opts*,int /*<<< orphan*/ ,int) ; 
 struct mg_connection* mg_connect_opt (struct mg_mgr*,char*,int /*<<< orphan*/ ,struct mg_connect_opts) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *test_connect_opts_error_string(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  struct mg_connect_opts opts;
  const char *error_string = NULL;

  memset(&opts, 0, sizeof(opts));
  opts.error_string = &error_string;

  mg_mgr_init(&mgr, NULL);
  ASSERT((nc = mg_connect_opt(&mgr, "127.0.0.1:65537", cb6, opts)) == NULL);
  ASSERT(error_string != NULL);
  ASSERT_STREQ(error_string, "cannot parse address");
  mg_mgr_free(&mgr);
  return NULL;
}
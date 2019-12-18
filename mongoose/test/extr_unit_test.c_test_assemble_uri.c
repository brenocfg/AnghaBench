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
struct mg_str {scalar_t__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_MG_STREQ (struct mg_str,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  mg_assemble_uri (struct mg_str*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mg_str*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct mg_str*) ; 
 struct mg_str mg_mk_str (char*) ; 

__attribute__((used)) static const char *test_assemble_uri(void) {
  struct mg_str scheme, path, uri;
  {
    ASSERT_EQ(mg_assemble_uri(NULL, NULL, NULL, 0, NULL, NULL, NULL, 0, &uri),
              0);
    ASSERT_MG_STREQ(uri, "");
  }

  {
    scheme = mg_mk_str("file");
    path = mg_mk_str("/foo/bar");
    ASSERT_EQ(
        mg_assemble_uri(&scheme, NULL, NULL, 0, &path, NULL, NULL, 0, &uri), 0);
    ASSERT_MG_STREQ(uri, "file:///foo/bar");
    free((void *) uri.p);
  }

  {
    scheme = mg_mk_str("file");
    path = mg_mk_str("/foo/.././bar/baz");
    ASSERT_EQ(
        mg_assemble_uri(&scheme, NULL, NULL, 0, &path, NULL, NULL, 0, &uri), 0);
    ASSERT_MG_STREQ(uri, "file:///foo/.././bar/baz");
    free((void *) uri.p);
    ASSERT_EQ(
        mg_assemble_uri(&scheme, NULL, NULL, 0, &path, NULL, NULL, 1, &uri), 0);
    ASSERT_MG_STREQ(uri, "file:///bar/baz");
    free((void *) uri.p);
  }

  return NULL;
}
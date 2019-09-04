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

/* Variables and functions */
 int /*<<< orphan*/  CHECK_MGNP (char*,int,char*) ; 

__attribute__((used)) static const char *test_mg_normalize_uri_path(void) {
  CHECK_MGNP("", 0, "");
  CHECK_MGNP("x", 0, "");
  CHECK_MGNP("/", 1, "/");
  CHECK_MGNP("//", 1, "//");
  CHECK_MGNP("/.", 1, "/");
  CHECK_MGNP("//.", 1, "//");
  CHECK_MGNP("/..", 1, "/");
  CHECK_MGNP("//..", 1, "/");
  CHECK_MGNP("///..", 1, "//");
  CHECK_MGNP("/./", 1, "/");
  CHECK_MGNP("/.//", 1, "//");
  CHECK_MGNP("/./.", 1, "/");
  CHECK_MGNP("/.//.", 1, "//");
  CHECK_MGNP("/foo", 1, "/foo");
  CHECK_MGNP("/foo/", 1, "/foo/");
  CHECK_MGNP("/foo/.", 1, "/foo/");
  CHECK_MGNP("/foo/./", 1, "/foo/");
  CHECK_MGNP("/foo/..", 1, "/");
  CHECK_MGNP("/foo/../", 1, "/");
  CHECK_MGNP("/foo/../bar", 1, "/bar");
  CHECK_MGNP("/foo/../bar/", 1, "/bar/");
  CHECK_MGNP("/foo/../../bar", 1, "/bar");
  CHECK_MGNP("/foo////bar/", 1, "/foo////bar/");
  /* No percent-decoding. */
  CHECK_MGNP("/fo%2fo/%2e%2e/%2e/bar", 1, "/fo%2fo/%2e%2e/%2e/bar");
  return NULL;
}
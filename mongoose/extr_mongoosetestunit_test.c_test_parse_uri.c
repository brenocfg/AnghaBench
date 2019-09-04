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
typedef  struct mg_str {char* p; unsigned int len; } const mg_str ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (unsigned int,int) ; 
 int /*<<< orphan*/  ASSERT_MG_STREQ (struct mg_str const,char*) ; 
 struct mg_str const MG_MK_STR (char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 unsigned int mg_assemble_uri (struct mg_str const*,struct mg_str const*,struct mg_str const*,unsigned int,struct mg_str const*,struct mg_str const*,struct mg_str const*,int /*<<< orphan*/ ,struct mg_str const*) ; 
 unsigned int mg_parse_uri (struct mg_str const,struct mg_str const*,struct mg_str const*,struct mg_str const*,unsigned int*,struct mg_str const*,struct mg_str const*,struct mg_str const*) ; 

__attribute__((used)) static const char *test_parse_uri(void) {
  struct mg_str uri_out;
  struct mg_str scheme, user_info, host, path, query, fragment;
  unsigned int port;
  {
    struct mg_str uri = MG_MK_STR("foo");
    ASSERT_EQ(mg_parse_uri(uri, NULL, NULL, NULL, NULL, NULL, NULL, NULL), 0);
  }

  {
    struct mg_str uri = MG_MK_STR("http://user:pw@host:80/foo?bar#baz");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);

    ASSERT_MG_STREQ(scheme, "http");
    ASSERT_MG_STREQ(user_info, "user:pw");
    ASSERT_MG_STREQ(host, "host");
    ASSERT_EQ(port, 80);
    ASSERT_MG_STREQ(path, "/foo");
    ASSERT_MG_STREQ(query, "bar");
    ASSERT_MG_STREQ(fragment, "baz");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    struct mg_str uri = MG_MK_STR("http://host:80/foo?bar");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);

    ASSERT_MG_STREQ(scheme, "http");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "host");
    ASSERT_EQ(port, 80);
    ASSERT_MG_STREQ(path, "/foo");
    ASSERT_MG_STREQ(query, "bar");
    ASSERT_MG_STREQ(fragment, "");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    struct mg_str uri = MG_MK_STR("http://host:80/foo#baz");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);

    ASSERT_MG_STREQ(scheme, "http");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "host");
    ASSERT_EQ(port, 80);
    ASSERT_MG_STREQ(path, "/foo");
    ASSERT_MG_STREQ(query, "");
    ASSERT_MG_STREQ(fragment, "baz");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    struct mg_str uri = MG_MK_STR("http://host:80/foo");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);

    ASSERT_MG_STREQ(scheme, "http");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "host");
    ASSERT_EQ(port, 80);
    ASSERT_MG_STREQ(path, "/foo");
    ASSERT_MG_STREQ(query, "");
    ASSERT_MG_STREQ(fragment, "");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    struct mg_str uri = MG_MK_STR("http://host/foo");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);

    ASSERT_MG_STREQ(scheme, "http");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "host");
    ASSERT_EQ(port, 0);
    ASSERT_MG_STREQ(path, "/foo");
    ASSERT_MG_STREQ(query, "");
    ASSERT_MG_STREQ(fragment, "");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    struct mg_str uri = MG_MK_STR("http://host");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);
    ASSERT_MG_STREQ(scheme, "http");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "host");
    ASSERT_EQ(port, 0);
    ASSERT_MG_STREQ(path, "");
    ASSERT_MG_STREQ(query, "");
    ASSERT_MG_STREQ(fragment, "");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    struct mg_str uri = MG_MK_STR("http://host:80");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);
    ASSERT_MG_STREQ(scheme, "http");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "host");
    ASSERT_EQ(port, 80);
    ASSERT_MG_STREQ(path, "");
    ASSERT_MG_STREQ(query, "");
    ASSERT_MG_STREQ(fragment, "");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    struct mg_str uri = MG_MK_STR("tcp://1.2.3.4:5678");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);
    ASSERT_MG_STREQ(scheme, "tcp");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "1.2.3.4");
    ASSERT_EQ(port, 5678);
    ASSERT_MG_STREQ(path, "");
    ASSERT_MG_STREQ(query, "");
    ASSERT_MG_STREQ(fragment, "");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    const struct mg_str uri = MG_MK_STR("tcp://[::1]:234");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);
    ASSERT_MG_STREQ(scheme, "tcp");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "[::1]");
    ASSERT_EQ(port, 234);
    ASSERT_EQ(path.len, 0);
    ASSERT_EQ(query.len, 0);
    ASSERT_EQ(fragment.len, 0);
    ASSERT_MG_STREQ(path, "");
    ASSERT_MG_STREQ(query, "");
    ASSERT_MG_STREQ(fragment, "");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    const struct mg_str uri = MG_MK_STR("tcp://[::1]");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);
    ASSERT_MG_STREQ(scheme, "tcp");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "[::1]");
    ASSERT_EQ(port, 0);
    ASSERT_MG_STREQ(path, "");
    ASSERT_MG_STREQ(query, "");
    ASSERT_MG_STREQ(fragment, "");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    const struct mg_str uri = MG_MK_STR("tcp://[::1");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              -1);
  }

  {
    struct mg_str uri = MG_MK_STR("host:80");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);
    ASSERT_MG_STREQ(scheme, "");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "host");
    ASSERT_EQ(port, 80);
    ASSERT_MG_STREQ(path, "");
    ASSERT_MG_STREQ(query, "");
    ASSERT_MG_STREQ(fragment, "");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    const struct mg_str uri = MG_MK_STR("1.2.3.4:56789");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);
    ASSERT_MG_STREQ(scheme, "");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "1.2.3.4");
    ASSERT_EQ(port, 56789);
    ASSERT_MG_STREQ(path, "");
    ASSERT_MG_STREQ(query, "");
    ASSERT_MG_STREQ(fragment, "");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    const struct mg_str uri = MG_MK_STR("[::1]:2345");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);
    ASSERT_MG_STREQ(scheme, "");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "[::1]");
    ASSERT_EQ(port, 2345);
    ASSERT_MG_STREQ(path, "");
    ASSERT_MG_STREQ(query, "");
    ASSERT_MG_STREQ(fragment, "");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    const struct mg_str uri = MG_MK_STR("[::1]");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);
    ASSERT_MG_STREQ(scheme, "");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "[::1]");
    ASSERT_EQ(port, 0);
    ASSERT_MG_STREQ(path, "");
    ASSERT_MG_STREQ(query, "");
    ASSERT_MG_STREQ(fragment, "");

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    struct mg_str uri = MG_MK_STR("host/foo");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);
    ASSERT_MG_STREQ(scheme, "");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "host");
    ASSERT_EQ(port, 0);
    ASSERT_MG_STREQ(path, "/foo");
    ASSERT_EQ(query.len, 0);
    ASSERT_EQ(fragment.len, 0);

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  {
    struct mg_str uri = MG_MK_STR("https://a.com/foo/x@y.z/fw.zip");
    ASSERT_EQ(mg_parse_uri(uri, &scheme, &user_info, &host, &port, &path,
                           &query, &fragment),
              0);
    ASSERT_MG_STREQ(scheme, "https");
    ASSERT_MG_STREQ(user_info, "");
    ASSERT_MG_STREQ(host, "a.com");
    ASSERT_EQ(port, 0);
    ASSERT_MG_STREQ(path, "/foo/x@y.z/fw.zip");
    ASSERT_EQ(query.len, 0);
    ASSERT_EQ(fragment.len, 0);

    ASSERT_EQ(mg_assemble_uri(&scheme, &user_info, &host, port, &path, &query,
                              &fragment, 0, &uri_out),
              0);
    ASSERT_MG_STREQ(uri_out, uri.p);
    free((void *) uri_out.p);
  }

  return NULL;
}
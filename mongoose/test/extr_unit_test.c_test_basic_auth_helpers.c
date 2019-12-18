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
typedef  int /*<<< orphan*/  user ;
struct mg_str {int dummy; } ;
struct mbuf {int len; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  pass ;
typedef  int /*<<< orphan*/  cases ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (int,int) ; 
 int /*<<< orphan*/  mbuf_free (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_init (struct mbuf*,int /*<<< orphan*/ ) ; 
 int memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_basic_auth_header (struct mg_str,struct mg_str,struct mbuf*) ; 
 struct mg_str mg_mk_str (char*) ; 
 struct mg_str mg_mk_str_n (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mg_parse_http_basic_auth (struct mg_str*,char const*,int,char const*,int) ; 
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static const char *test_basic_auth_helpers() {
  struct mbuf buf;
  mbuf_init(&buf, 0);
  mg_basic_auth_header(mg_mk_str("foo"), mg_mk_str("bar"), &buf);
  ASSERT_EQ(buf.len, 35);
  ASSERT_EQ(memcmp(buf.buf, "Authorization: Basic Zm9vOmJhcg==\r\n", 35), 0);

  buf.len = 0;
  mg_basic_auth_header(mg_mk_str("foo:bar"), mg_mk_str_n(NULL, 0), &buf);
  ASSERT_EQ(buf.len, 35);
  ASSERT_EQ(memcmp(buf.buf, "Authorization: Basic Zm9vOmJhcg==\r\n", 35), 0);

  mbuf_free(&buf);

  {
    char user[256];
    char pass[256];
    size_t i;

    struct {
      const char *hdr;
      const char *user;
      const char *pass;
      int res;
    } cases[] = {
        {"Basic Zm9vOmJhcg==", "foo", "bar", 0},         /* foo:bar */
        {"Basic Zm9v", "foo", "", 0},                    /* foo */
        {"Basic Zm9vOmJhcjpiYXo=", "foo", "bar:baz", 0}, /* foo:bar:baz */
        {"Basic Zm9vOg==", "foo", "", 0},                /* foo: */
        {"Basic OmJhcg==", "", "", -1},                  /* :bar */
    };

    for (i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
      struct mg_str hdr = mg_mk_str(cases[i].hdr);
      int res;

      memset(user, 0, sizeof(user));
      memset(pass, 0, sizeof(pass));
      res = mg_parse_http_basic_auth(&hdr, user, sizeof(user), pass,
                                     sizeof(pass));
      ASSERT_EQ(res, cases[i].res);
      ASSERT_EQ(strcmp(user, cases[i].user), 0);
      ASSERT_EQ(strcmp(pass, cases[i].pass), 0);
    }
  }
  return NULL;
}
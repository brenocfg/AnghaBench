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
struct mg_str {int dummy; } ;
typedef  int /*<<< orphan*/  nonce ;
typedef  int /*<<< orphan*/  auth_hdr ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_STREQ (char*,char*) ; 
 int /*<<< orphan*/  ASSERT_STREQ_NZ (char*,char*) ; 
 int FETCH_BUF_SIZE ; 
 int /*<<< orphan*/  fetch_http (char*,char*,char*) ; 
 int /*<<< orphan*/  fetch_http2 (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  mg_http_create_digest_auth_header (char*,int,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  mg_http_parse_header (struct mg_str*,char*,char*,int) ; 
 struct mg_str mg_mk_str (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 
 int strlen (char*) ; 
 unsigned long strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const char *test_http_digest_auth(void) {
  char buf[FETCH_BUF_SIZE], auth_hdr[200];
  char nonce[40];
  struct mg_str bufstr;

  /* Test digest authorization popup - per-directory auth file */
  fetch_http(buf, "%s", "GET /data/auth/a.txt?a=b HTTP/1.0\r\n\r\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 401");
  bufstr = mg_mk_str(buf);
  ASSERT_GT(mg_http_parse_header(&bufstr, "nonce", nonce, sizeof(nonce)), 0);
  buf[0] = '\0';
  /* Per-endpoint auth config */
  fetch_http(buf, "%s", "GET /secret HTTP/1.0\r\n\r\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 401");
#if MG_ENABLE_HTTP_STREAMING_MULTIPART
  fetch_http(buf, "%s",
             "POST /secret/upload HTTP/1.0\r\n"
             "Content-Type: multipart/form-data;boundary=omgwtf\r\n"
             "\r\n--omgwtf\r\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 401");
#endif

  /* Test digest authorization success */
  mg_http_create_digest_auth_header(auth_hdr, sizeof(auth_hdr), "GET",
                                    "/data/auth/a.txt?a=b", "foo.com", "joe",
                                    "doe", nonce);
  fetch_http(buf, "GET /data/auth/a.txt?a=b HTTP/1.0\r\n%s\r\n\r\n", auth_hdr);
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 200");
  ASSERT_STREQ(buf + strlen(buf) - 7, "\r\n\r\nhi\n");
  mg_http_create_digest_auth_header(auth_hdr, sizeof(auth_hdr), "GET",
                                    "/secret", "foo.com", "joe", "doe", nonce);
  fetch_http(buf, "GET /secret HTTP/1.0\r\n%s\r\n\r\n", auth_hdr);
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 200");
  ASSERT_STREQ(buf + strlen(buf) - 7, "Secret!");

  /* Test digest authorization failure with non-existing passwords file */
  mg_http_create_digest_auth_header(auth_hdr, sizeof(auth_hdr), "GET",
                                    "/data/auth/a.txt?a=b", "foo.com", "joe",
                                    "doe", nonce);
  fetch_http2(buf, "data/auth/non-existing-passwords.txt",
              "GET /data/auth/a.txt?a=b HTTP/1.0\r\n%s\r\n\r\n", auth_hdr);
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 200");
  ASSERT_STREQ(buf + strlen(buf) - 7, "\r\n\r\nhi\n");
  mg_http_create_digest_auth_header(auth_hdr, sizeof(auth_hdr), "GET",
                                    "/secret", "foo.com", "joe", "doe", nonce);
  fetch_http2(buf, "data/auth/non-existing-passwords.txt",
              "GET /secret HTTP/1.0\r\n%s\r\n\r\n", auth_hdr);
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 401");

  /* Test digest authorization failure with old nonce */
  {
    /*
     * Add 10 seconds to the nonce value, so that it'll be in the future
     * and mg_check_nonce() should fail.
     */
    unsigned long nonce_val = strtoul(nonce, NULL, 16);
    sprintf(nonce, "%lx", nonce_val + 10);

    mg_http_create_digest_auth_header(auth_hdr, sizeof(auth_hdr), "GET",
                                      "/data/auth/a.txt?a=b", "foo.com", "joe",
                                      "doe", nonce);
    fetch_http(buf, "GET /data/auth/a.txt?a=b HTTP/1.0\r\n%s\r\n\r\n",
               auth_hdr);
    ASSERT_STREQ_NZ(buf, "HTTP/1.1 401");

    mg_http_create_digest_auth_header(auth_hdr, sizeof(auth_hdr), "GET",
                                      "/secret", "foo.com", "joe", "doe",
                                      nonce);

    fetch_http(buf, "GET /secret HTTP/1.0\r\n%s\r\n\r\n", auth_hdr);
    ASSERT_STREQ_NZ(buf, "HTTP/1.1 401");

    /* Make nonce 1-hour-old, so mg_check_nonce() should fail again. */
    sprintf(nonce, "%lx", nonce_val - 60 * 60);

    mg_http_create_digest_auth_header(auth_hdr, sizeof(auth_hdr), "GET",
                                      "/data/auth/a.txt?a=b", "foo.com", "joe",
                                      "doe", nonce);
    fetch_http(buf, "GET /data/auth/a.txt?a=b HTTP/1.0\r\n%s\r\n\r\n",
               auth_hdr);
    ASSERT_STREQ_NZ(buf, "HTTP/1.1 401");

    /* Renew nonce to represent the actual nonce from the server */
    bufstr = mg_mk_str(buf);
    ASSERT_GT(mg_http_parse_header(&bufstr, "nonce", nonce, sizeof(nonce)), 0);
  }

  /* Test that passwords file is hidden from view */
  mg_http_create_digest_auth_header(auth_hdr, sizeof(auth_hdr), "GET",
                                    "/data/auth/p%61sswords%2etxt", "foo.com",
                                    "joe", "doe", nonce);
  fetch_http(buf,
             "GET /data/auth/p%%61sswords%%2etxt HTTP/1.0\r\n"
             "%s\r\n\r\n",
             auth_hdr);
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 404");
  /* On case-insensitive filesystems too. */
  mg_http_create_digest_auth_header(auth_hdr, sizeof(auth_hdr), "GET",
                                    "/data/auth/Passwords.txt", "foo.com",
                                    "joe", "doe", nonce);
  fetch_http(buf,
             "GET /data/auth/Passwords.txt HTTP/1.0\r\n"
             "%s\r\n\r\n",
             auth_hdr);
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 404");

  return NULL;
}
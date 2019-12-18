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
struct mg_str {int len; char* p; } ;
struct mbuf {char* buf; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  mbuf_append (struct mbuf*,char*,int) ; 
 int /*<<< orphan*/  mbuf_free (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_init (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_normalize_uri_path (struct mg_str const*,struct mg_str*) ; 
 struct mg_str mg_strdup (struct mg_str const) ; 
 int sprintf (char*,char*,unsigned int) ; 

int mg_assemble_uri(const struct mg_str *scheme, const struct mg_str *user_info,
                    const struct mg_str *host, unsigned int port,
                    const struct mg_str *path, const struct mg_str *query,
                    const struct mg_str *fragment, int normalize_path,
                    struct mg_str *uri) {
  int result = -1;
  struct mbuf out;
  mbuf_init(&out, 0);

  if (scheme != NULL && scheme->len > 0) {
    mbuf_append(&out, scheme->p, scheme->len);
    mbuf_append(&out, "://", 3);
  }

  if (user_info != NULL && user_info->len > 0) {
    mbuf_append(&out, user_info->p, user_info->len);
    mbuf_append(&out, "@", 1);
  }

  if (host != NULL && host->len > 0) {
    mbuf_append(&out, host->p, host->len);
  }

  if (port != 0) {
    char port_str[20];
    int port_str_len = sprintf(port_str, ":%u", port);
    mbuf_append(&out, port_str, port_str_len);
  }

  if (path != NULL && path->len > 0) {
    if (normalize_path) {
      struct mg_str npath = mg_strdup(*path);
      if (npath.len != path->len) goto out;
      if (!mg_normalize_uri_path(path, &npath)) {
        free((void *) npath.p);
        goto out;
      }
      mbuf_append(&out, npath.p, npath.len);
      free((void *) npath.p);
    } else {
      mbuf_append(&out, path->p, path->len);
    }
  } else if (normalize_path) {
    mbuf_append(&out, "/", 1);
  }

  if (query != NULL && query->len > 0) {
    mbuf_append(&out, "?", 1);
    mbuf_append(&out, query->p, query->len);
  }

  if (fragment != NULL && fragment->len > 0) {
    mbuf_append(&out, "#", 1);
    mbuf_append(&out, fragment->p, fragment->len);
  }

  result = 0;

out:
  if (result == 0) {
    uri->p = out.buf;
    uri->len = out.len;
  } else {
    mbuf_free(&out);
    uri->p = NULL;
    uri->len = 0;
  }
  return result;
}
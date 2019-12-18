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
struct mg_str {char const* p; size_t len; } ;
typedef  int /*<<< orphan*/  cd ;

/* Variables and functions */
 int /*<<< orphan*/  MG_FREE (char*) ; 
 size_t mg_get_line_len (char const*,size_t) ; 
 int mg_http_get_request_len (char const*,size_t) ; 
 int /*<<< orphan*/  mg_http_parse_header2 (struct mg_str*,char*,char**,size_t) ; 
 scalar_t__ mg_ncasecmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,size_t) ; 

size_t mg_parse_multipart(const char *buf, size_t buf_len, char *var_name,
                          size_t var_name_len, char *file_name,
                          size_t file_name_len, const char **data,
                          size_t *data_len) {
  static const char cd[] = "Content-Disposition: ";
  size_t hl, bl, n, ll, pos, cdl = sizeof(cd) - 1;
  int shl;

  if (buf == NULL || buf_len <= 0) return 0;
  if ((shl = mg_http_get_request_len(buf, buf_len)) <= 0) return 0;
  hl = shl;
  if (buf[0] != '-' || buf[1] != '-' || buf[2] == '\n') return 0;

  /* Get boundary length */
  bl = mg_get_line_len(buf, buf_len);

  /* Loop through headers, fetch variable name and file name */
  var_name[0] = file_name[0] = '\0';
  for (n = bl; (ll = mg_get_line_len(buf + n, hl - n)) > 0; n += ll) {
    if (mg_ncasecmp(cd, buf + n, cdl) == 0) {
      struct mg_str header;
      header.p = buf + n + cdl;
      header.len = ll - (cdl + 2);
      {
        char *var_name2 = var_name;
        mg_http_parse_header2(&header, "name", &var_name2, var_name_len);
        /* TODO: handle reallocated buffer correctly */
        if (var_name2 != var_name) {
          MG_FREE(var_name2);
          var_name[0] = '\0';
        }
      }
      {
        char *file_name2 = file_name;
        mg_http_parse_header2(&header, "filename", &file_name2, file_name_len);
        /* TODO: handle reallocated buffer correctly */
        if (file_name2 != file_name) {
          MG_FREE(file_name2);
          file_name[0] = '\0';
        }
      }
    }
  }

  /* Scan through the body, search for terminating boundary */
  for (pos = hl; pos + (bl - 2) < buf_len; pos++) {
    if (buf[pos] == '-' && !strncmp(buf, &buf[pos], bl - 2)) {
      if (data_len != NULL) *data_len = (pos - 2) - hl;
      if (data != NULL) *data = buf + hl;
      return pos;
    }
  }

  return 0;
}
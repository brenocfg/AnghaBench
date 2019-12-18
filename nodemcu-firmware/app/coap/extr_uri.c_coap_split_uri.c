#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int port; int /*<<< orphan*/  query; int /*<<< orphan*/  path; int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ coap_uri_t ;

/* Variables and functions */
 int COAP_DEFAULT_PORT ; 
 scalar_t__ COAP_DEFAULT_SCHEME ; 
 int /*<<< orphan*/  COAP_SET_STR (int /*<<< orphan*/ *,size_t,unsigned char*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 unsigned char tolower (unsigned char) ; 

int coap_split_uri(unsigned char *str_var, size_t len, coap_uri_t *uri) {
  unsigned char *p, *q;
  int secure = 0, res = 0;

  if (!str_var || !uri)
    return -1;

  memset(uri, 0, sizeof(coap_uri_t));
  uri->port = COAP_DEFAULT_PORT;

  /* search for scheme */
  p = str_var;
  if (*p == '/') {
    q = p;
    goto path;
  }

  q = (unsigned char *)COAP_DEFAULT_SCHEME;
  while (len && *q && tolower(*p) == *q) {
    ++p; ++q; --len;
  }

  /* If q does not point to the string end marker '\0', the schema
   * identifier is wrong. */
  if (*q) {
    res = -1;
    goto error;
  }

  /* There might be an additional 's', indicating the secure version: */
  if (len && (secure = tolower(*p) == 's')) {
    ++p; --len;
  }

  q = (unsigned char *)"://";
  while (len && *q && tolower(*p) == *q) {
    ++p; ++q; --len;
  }

  if (*q) {
    res = -2;
    goto error;
  }

  /* p points to beginning of Uri-Host */
  q = p;
  if (len && *p == '[') {	/* IPv6 address reference */
    ++p;

    while (len && *q != ']') {
      ++q; --len;
    }

    if (!len || *q != ']' || p == q) {
      res = -3;
      goto error;
    }

    COAP_SET_STR(&uri->host, q - p, p);
    ++q; --len;
  } else {			/* IPv4 address or FQDN */
    while (len && *q != ':' && *q != '/' && *q != '?') {
      *q = tolower(*q);
      ++q;
      --len;
    }

    if (p == q) {
      res = -3;
      goto error;
    }

    COAP_SET_STR(&uri->host, q - p, p);
  }

  /* check for Uri-Port */
  if (len && *q == ':') {
    p = ++q;
    --len;

    while (len && isdigit(*q)) {
      ++q;
      --len;
    }

    if (p < q) {		/* explicit port number given */
      int uri_port = 0;

      while (p < q)
	     uri_port = uri_port * 10 + (*p++ - '0');

      uri->port = uri_port;
    }
  }

 path:		 /* at this point, p must point to an absolute path */

  if (!len)
    goto end;

  if (*q == '/') {
    p = ++q;
    --len;

    while (len && *q != '?') {
      ++q;
      --len;
    }

    if (p < q) {
      COAP_SET_STR(&uri->path, q - p, p);
      p = q;
    }
  }

  /* Uri_Query */
  if (len && *p == '?') {
    ++p;
    --len;
    COAP_SET_STR(&uri->query, len, p);
    len = 0;
  }

  end:
  return len ? -1 : 0;

  error:
  return res;
}
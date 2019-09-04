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
struct mg_str {int /*<<< orphan*/  p; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LL_DEBUG ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mkmd5resp (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ mg_ncasecmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mg_vcmp (struct mg_str*,char*) ; 
 int sscanf (char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int mg_check_digest_auth(struct mg_str method, struct mg_str uri,
                         struct mg_str username, struct mg_str cnonce,
                         struct mg_str response, struct mg_str qop,
                         struct mg_str nc, struct mg_str nonce,
                         struct mg_str auth_domain, FILE *fp) {
  char buf[128], f_user[sizeof(buf)], f_ha1[sizeof(buf)], f_domain[sizeof(buf)];
  char exp_resp[33];

  /*
   * Read passwords file line by line. If should have htdigest format,
   * i.e. each line should be a colon-separated sequence:
   * USER_NAME:DOMAIN_NAME:HA1_HASH_OF_USER_DOMAIN_AND_PASSWORD
   */
  while (fgets(buf, sizeof(buf), fp) != NULL) {
    if (sscanf(buf, "%[^:]:%[^:]:%s", f_user, f_domain, f_ha1) == 3 &&
        mg_vcmp(&username, f_user) == 0 &&
        mg_vcmp(&auth_domain, f_domain) == 0) {
      /* Username and domain matched, check the password */
      mg_mkmd5resp(method.p, method.len, uri.p, uri.len, f_ha1, strlen(f_ha1),
                   nonce.p, nonce.len, nc.p, nc.len, cnonce.p, cnonce.len,
                   qop.p, qop.len, exp_resp);
      LOG(LL_DEBUG, ("%.*s %s %.*s %s", (int) username.len, username.p,
                     f_domain, (int) response.len, response.p, exp_resp));
      return mg_ncasecmp(response.p, exp_resp, strlen(exp_resp)) == 0;
    }
  }

  /* None of the entries in the passwords file matched - return failure */
  return 0;
}
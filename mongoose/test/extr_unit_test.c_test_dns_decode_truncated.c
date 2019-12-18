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
struct in_addr {scalar_t__ s_addr; } ;
typedef  struct in_addr uint16_t ;
typedef  int /*<<< orphan*/  tiny ;
struct mg_dns_resource_record {int rtype; int /*<<< orphan*/  name; int /*<<< orphan*/  rdata; } ;
struct mg_dns_message {int num_questions; int num_answers; struct mg_dns_resource_record* answers; struct mg_dns_resource_record* questions; } ;
typedef  int /*<<< orphan*/  src ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  ina ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MG_DNS_A_RECORD ; 
 int /*<<< orphan*/  MG_DNS_CNAME_RECORD ; 
 int /*<<< orphan*/  WONDER (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ inet_addr (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char const*,int) ; 
 struct mg_dns_resource_record* mg_dns_next_record (struct mg_dns_message*,int /*<<< orphan*/ ,struct mg_dns_resource_record*) ; 
 int mg_dns_parse_record_data (struct mg_dns_message*,struct mg_dns_resource_record*,struct in_addr*,int) ; 
 scalar_t__ mg_dns_uncompress_name (struct mg_dns_message*,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ mg_parse_dns (char const*,int,struct mg_dns_message*) ; 
 int /*<<< orphan*/  printf (char*,void*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,scalar_t__) ; 

__attribute__((used)) static const char *test_dns_decode_truncated(void) {
  struct mg_dns_message msg;
  char name[256];
  const char *hostname = "go.cesanta.com";
  const char *cname = "ghs.googlehosted.com";
  struct mg_dns_resource_record *r;
  uint16_t tiny;
  struct in_addr ina;
  int n;
  int i;

  const unsigned char src[] = {
      0xa1, 0x00, 0x81, 0x80, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
      0x02, 0x67, 0x6f, 0x07, 0x63, 0x65, 0x73, 0x61, 0x6e, 0x74, 0x61, 0x03,
      0x63, 0x6f, 0x6d, 0x00, 0x00, 0x01, 0x00, 0x01, 0xc0, 0x0c, 0x00, 0x05,
      0x00, 0x01, 0x00, 0x00, 0x09, 0x52, 0x00, 0x13, 0x03, 0x67, 0x68, 0x73,
      0x0c, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x68, 0x6f, 0x73, 0x74, 0x65,
      0x64, 0xc0, 0x17, 0xc0, 0x2c, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
      0x2b, 0x00, 0x04, 0x4a, 0x7d, 0x88, 0x79};
  char *pkt = NULL;

#define WONDER(expr) \
  if (!(expr)) continue

  for (i = sizeof(src) - 1; i > 0; i--) {
    free(pkt);
    pkt = (char *) malloc(i);
    memcpy(pkt, src, i);

    WONDER(mg_parse_dns((const char *) pkt, i, &msg) == 0);
    WONDER(msg.num_questions == 1);
    WONDER(msg.num_answers == 2);

    r = &msg.questions[0];
    WONDER(mg_dns_uncompress_name(&msg, &r->name, name, sizeof(name)) ==
           strlen(hostname));
    WONDER(strncmp(name, hostname, strlen(hostname)) == 0);

    r = &msg.answers[0];
    WONDER(mg_dns_uncompress_name(&msg, &r->name, name, sizeof(name)) ==
           strlen(hostname));
    WONDER(strncmp(name, hostname, strlen(hostname)) == 0);

    WONDER(mg_dns_uncompress_name(&msg, &r->rdata, name, sizeof(name)) ==
           strlen(cname));
    WONDER(strncmp(name, cname, strlen(cname)) == 0);

    r = &msg.answers[1];
    WONDER(mg_dns_uncompress_name(&msg, &r->name, name, sizeof(name)) ==
           strlen(cname));
    WONDER(strncmp(name, cname, strlen(cname)) == 0);
    WONDER(mg_dns_parse_record_data(&msg, r, &tiny, sizeof(tiny)) == -1);
    WONDER(mg_dns_parse_record_data(&msg, r, &ina, sizeof(ina)) == 0);
    WONDER(ina.s_addr == inet_addr("74.125.136.121"));

    /* Test iteration */
    n = 0;
    r = NULL;
    while ((r = mg_dns_next_record(&msg, MG_DNS_A_RECORD, r))) {
      n++;
    }
    WONDER(n == 1);

    n = 0;
    r = NULL;
    while ((r = mg_dns_next_record(&msg, MG_DNS_CNAME_RECORD, r))) {
      n++;
    }
    WONDER(n == 1);

    /* Test unknown record type */
    r = mg_dns_next_record(&msg, MG_DNS_A_RECORD, r);
    WONDER(r != NULL);
    printf("GOT %p\n", (void *) r);
    r->rtype = 0xff;
    WONDER(mg_dns_parse_record_data(&msg, r, &ina, sizeof(ina)) == -1);

    ASSERT("Should have failed" == NULL);
  }
  free(pkt);
  return NULL;
}
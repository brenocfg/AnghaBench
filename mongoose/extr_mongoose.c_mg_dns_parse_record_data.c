#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p; } ;
struct mg_dns_resource_record {int rtype; TYPE_2__ rdata; } ;
struct TYPE_3__ {scalar_t__ len; scalar_t__ p; } ;
struct mg_dns_message {TYPE_1__ pkt; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  MG_DNS_AAAA_RECORD 130 
#define  MG_DNS_A_RECORD 129 
#define  MG_DNS_CNAME_RECORD 128 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mg_dns_uncompress_name (struct mg_dns_message*,TYPE_2__*,char*,size_t) ; 

int mg_dns_parse_record_data(struct mg_dns_message *msg,
                             struct mg_dns_resource_record *rr, void *data,
                             size_t data_len) {
  switch (rr->rtype) {
    case MG_DNS_A_RECORD:
      if (data_len < sizeof(struct in_addr)) {
        return -1;
      }
      if (rr->rdata.p + data_len > msg->pkt.p + msg->pkt.len) {
        return -1;
      }
      memcpy(data, rr->rdata.p, data_len);
      return 0;
#if MG_ENABLE_IPV6
    case MG_DNS_AAAA_RECORD:
      if (data_len < sizeof(struct in6_addr)) {
        return -1; /* LCOV_EXCL_LINE */
      }
      memcpy(data, rr->rdata.p, data_len);
      return 0;
#endif
    case MG_DNS_CNAME_RECORD:
      mg_dns_uncompress_name(msg, &rr->rdata, (char *) data, data_len);
      return 0;
  }

  return -1;
}
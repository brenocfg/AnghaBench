#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pkt_scr {int n; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; TYPE_2__* member_0; } ;
typedef  int /*<<< orphan*/  coap_rw_buffer_t ;
typedef  int /*<<< orphan*/  coap_parse_iterator_t ;
struct TYPE_5__ {int numopts; TYPE_1__* opts; } ;
typedef  TYPE_2__ coap_packet_t ;
struct TYPE_4__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  COAP_OPTION_URI_QUERY ; 
 int /*<<< orphan*/  coap_parse_iterator_init (unsigned char*,size_t,char,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coap_split_path_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pkt_scr*) ; 
 int /*<<< orphan*/  write_option ; 

int coap_split_query(coap_rw_buffer_t *scratch, coap_packet_t *pkt, const unsigned char *s, size_t length) {
  struct pkt_scr tmp = { pkt, scratch, 0 };
  coap_parse_iterator_t pi;

  coap_parse_iterator_init((unsigned char *)s, length,
         '&', (unsigned char *)"#", 1, &pi);

  coap_split_path_impl(&pi, write_option, &tmp);

  int i;
  for(i=0;i<tmp.n;i++){
    pkt->opts[pkt->numopts - i - 1].num = COAP_OPTION_URI_QUERY;
  }

  return tmp.n;
}
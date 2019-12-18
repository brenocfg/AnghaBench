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
typedef  int /*<<< orphan*/  uint8_t ;
struct msg_parse {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  prs ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  memset (struct msg_parse*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_packet (int /*<<< orphan*/ *,struct msg_parse*,scalar_t__) ; 
 scalar_t__ region ; 
 scalar_t__ regional_create () ; 
 int /*<<< orphan*/  sldns_buffer_init_frm_data (int /*<<< orphan*/ *,void*,size_t) ; 

int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len)
{
	if (!region) {
		region = regional_create();
		if (!region) {
			abort();
		}
}
	sldns_buffer pktbuf;
	sldns_buffer_init_frm_data(&pktbuf, (void*)buf, len);

	struct msg_parse prs;
	memset(&prs, 0, sizeof(prs));
	parse_packet(&pktbuf, &prs, region);
	return 0;
}
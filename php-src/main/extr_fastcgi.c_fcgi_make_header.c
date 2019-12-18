#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fcgi_request_type ;
struct TYPE_3__ {unsigned char contentLengthB0; unsigned char contentLengthB1; unsigned char paddingLength; unsigned char requestIdB0; unsigned char requestIdB1; int /*<<< orphan*/  version; int /*<<< orphan*/  type; scalar_t__ reserved; } ;
typedef  TYPE_1__ fcgi_header ;

/* Variables and functions */
 int /*<<< orphan*/  FCGI_VERSION_1 ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int fcgi_make_header(fcgi_header *hdr, fcgi_request_type type, int req_id, int len)
{
	int pad = ((len + 7) & ~7) - len;

	hdr->contentLengthB0 = (unsigned char)(len & 0xff);
	hdr->contentLengthB1 = (unsigned char)((len >> 8) & 0xff);
	hdr->paddingLength = (unsigned char)pad;
	hdr->requestIdB0 = (unsigned char)(req_id & 0xff);
	hdr->requestIdB1 = (unsigned char)((req_id >> 8) & 0xff);
	hdr->reserved = 0;
	hdr->type = type;
	hdr->version = FCGI_VERSION_1;
	if (pad) {
		memset(((unsigned char*)hdr) + sizeof(fcgi_header) + len, 0, pad);
	}
	return pad;
}
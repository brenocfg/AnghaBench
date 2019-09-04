#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fcgi_request_type ;
struct TYPE_5__ {TYPE_2__* out_hdr; scalar_t__ out_pos; } ;
typedef  TYPE_1__ fcgi_request ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ fcgi_header ;

/* Variables and functions */

__attribute__((used)) static inline fcgi_header* open_packet(fcgi_request *req, fcgi_request_type type)
{
	req->out_hdr = (fcgi_header*) req->out_pos;
	req->out_hdr->type = type;
	req->out_pos += sizeof(fcgi_header);
	return req->out_hdr;
}
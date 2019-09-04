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
struct TYPE_4__ {unsigned int length; } ;
struct sclp_vt220_sccb {TYPE_2__ evbuf; } ;
struct TYPE_3__ {scalar_t__ sccb; } ;
struct sclp_vt220_request {TYPE_1__ sclp_req; } ;
struct evbuf_header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int
sclp_vt220_chars_stored(struct sclp_vt220_request *request)
{
	struct sclp_vt220_sccb *sccb;
	sccb = (struct sclp_vt220_sccb *) request->sclp_req.sccb;
	return sccb->evbuf.length - sizeof(struct evbuf_header);
}
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
struct sctp_stream {int outcnt; int incnt; } ;
struct TYPE_4__ {scalar_t__ mid; } ;
struct TYPE_3__ {scalar_t__ mid_uo; scalar_t__ mid; } ;

/* Variables and functions */
 TYPE_2__* SCTP_SI (struct sctp_stream*,int) ; 
 TYPE_1__* SCTP_SO (struct sctp_stream*,int) ; 

void sctp_stream_clear(struct sctp_stream *stream)
{
	int i;

	for (i = 0; i < stream->outcnt; i++) {
		SCTP_SO(stream, i)->mid = 0;
		SCTP_SO(stream, i)->mid_uo = 0;
	}

	for (i = 0; i < stream->incnt; i++)
		SCTP_SI(stream, i)->mid = 0;
}
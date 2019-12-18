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
struct fw_unit {int dummy; } ;
struct amdtp_stream {int dummy; } ;
struct amdtp_dot {int dummy; } ;
typedef  enum cip_flags { ____Placeholder_cip_flags } cip_flags ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;
typedef  int /*<<< orphan*/  amdtp_stream_process_ctx_payloads_t ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 int CIP_BLOCKING ; 
 int /*<<< orphan*/  CIP_FMT_AM ; 
 int CIP_NONBLOCKING ; 
 int amdtp_stream_init (struct amdtp_stream*,struct fw_unit*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_ir_ctx_payloads ; 
 int /*<<< orphan*/  process_it_ctx_payloads ; 

int amdtp_dot_init(struct amdtp_stream *s, struct fw_unit *unit,
		 enum amdtp_stream_direction dir)
{
	amdtp_stream_process_ctx_payloads_t process_ctx_payloads;
	enum cip_flags flags;

	// Use different mode between incoming/outgoing.
	if (dir == AMDTP_IN_STREAM) {
		flags = CIP_NONBLOCKING;
		process_ctx_payloads = process_ir_ctx_payloads;
	} else {
		flags = CIP_BLOCKING;
		process_ctx_payloads = process_it_ctx_payloads;
	}

	return amdtp_stream_init(s, unit, dir, flags, CIP_FMT_AM,
				process_ctx_payloads, sizeof(struct amdtp_dot));
}
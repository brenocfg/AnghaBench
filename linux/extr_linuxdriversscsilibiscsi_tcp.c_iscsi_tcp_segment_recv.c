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
struct iscsi_tcp_conn {int /*<<< orphan*/  iscsi_conn; } ;
struct iscsi_segment {scalar_t__ copied; scalar_t__ data; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_TCP (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  iscsi_tcp_segment_done (struct iscsi_tcp_conn*,struct iscsi_segment*,int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,unsigned int) ; 
 unsigned int min (unsigned int,scalar_t__) ; 

__attribute__((used)) static int
iscsi_tcp_segment_recv(struct iscsi_tcp_conn *tcp_conn,
		       struct iscsi_segment *segment, const void *ptr,
		       unsigned int len)
{
	unsigned int copy = 0, copied = 0;

	while (!iscsi_tcp_segment_done(tcp_conn, segment, 1, copy)) {
		if (copied == len) {
			ISCSI_DBG_TCP(tcp_conn->iscsi_conn,
				      "copied %d bytes\n", len);
			break;
		}

		copy = min(len - copied, segment->size - segment->copied);
		ISCSI_DBG_TCP(tcp_conn->iscsi_conn, "copying %d\n", copy);
		memcpy(segment->data + segment->copied, ptr + copied, copy);
		copied += copy;
	}
	return copied;
}
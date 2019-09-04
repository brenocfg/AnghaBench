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
struct iscsi_segment {int /*<<< orphan*/  digest_len; int /*<<< orphan*/  digest; int /*<<< orphan*/  recv_digest; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_TCP (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
iscsi_tcp_dgst_verify(struct iscsi_tcp_conn *tcp_conn,
		      struct iscsi_segment *segment)
{
	if (!segment->digest_len)
		return 1;

	if (memcmp(segment->recv_digest, segment->digest,
		   segment->digest_len)) {
		ISCSI_DBG_TCP(tcp_conn->iscsi_conn, "digest mismatch\n");
		return 0;
	}

	return 1;
}
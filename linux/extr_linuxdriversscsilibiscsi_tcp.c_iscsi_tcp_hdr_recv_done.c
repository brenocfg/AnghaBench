#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct iscsi_hdr* hdr; scalar_t__ hdr_buf; } ;
struct iscsi_tcp_conn {TYPE_3__ in; int /*<<< orphan*/  rx_hash; struct iscsi_conn* iscsi_conn; } ;
struct iscsi_segment {int copied; unsigned int total_size; unsigned int size; scalar_t__ digest_len; int /*<<< orphan*/  digest; scalar_t__ total_copied; int /*<<< orphan*/  recv_digest; } ;
struct iscsi_hdr {int hlength; } ;
struct iscsi_conn {TYPE_2__* session; scalar_t__ hdrdgst_en; } ;
struct TYPE_5__ {TYPE_1__* tt; } ;
struct TYPE_4__ {int caps; } ;

/* Variables and functions */
 int CAP_DIGEST_OFFLOAD ; 
 scalar_t__ ISCSI_DIGEST_SIZE ; 
 int ISCSI_ERR_AHSLEN ; 
 int ISCSI_ERR_HDR_DGST ; 
 int /*<<< orphan*/  iscsi_tcp_dgst_header (int /*<<< orphan*/ ,struct iscsi_hdr*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_tcp_dgst_verify (struct iscsi_tcp_conn*,struct iscsi_segment*) ; 
 int iscsi_tcp_hdr_dissect (struct iscsi_conn*,struct iscsi_hdr*) ; 
 int /*<<< orphan*/  iscsi_tcp_segment_splice_digest (struct iscsi_segment*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iscsi_tcp_hdr_recv_done(struct iscsi_tcp_conn *tcp_conn,
			struct iscsi_segment *segment)
{
	struct iscsi_conn *conn = tcp_conn->iscsi_conn;
	struct iscsi_hdr *hdr;

	/* Check if there are additional header segments
	 * *prior* to computing the digest, because we
	 * may need to go back to the caller for more.
	 */
	hdr = (struct iscsi_hdr *) tcp_conn->in.hdr_buf;
	if (segment->copied == sizeof(struct iscsi_hdr) && hdr->hlength) {
		/* Bump the header length - the caller will
		 * just loop around and get the AHS for us, and
		 * call again. */
		unsigned int ahslen = hdr->hlength << 2;

		/* Make sure we don't overflow */
		if (sizeof(*hdr) + ahslen > sizeof(tcp_conn->in.hdr_buf))
			return ISCSI_ERR_AHSLEN;

		segment->total_size += ahslen;
		segment->size += ahslen;
		return 0;
	}

	/* We're done processing the header. See if we're doing
	 * header digests; if so, set up the recv_digest buffer
	 * and go back for more. */
	if (conn->hdrdgst_en &&
	    !(conn->session->tt->caps & CAP_DIGEST_OFFLOAD)) {
		if (segment->digest_len == 0) {
			/*
			 * Even if we offload the digest processing we
			 * splice it in so we can increment the skb/segment
			 * counters in preparation for the data segment.
			 */
			iscsi_tcp_segment_splice_digest(segment,
							segment->recv_digest);
			return 0;
		}

		iscsi_tcp_dgst_header(tcp_conn->rx_hash, hdr,
				      segment->total_copied - ISCSI_DIGEST_SIZE,
				      segment->digest);

		if (!iscsi_tcp_dgst_verify(tcp_conn, segment))
			return ISCSI_ERR_HDR_DGST;
	}

	tcp_conn->in.hdr = hdr;
	return iscsi_tcp_hdr_dissect(conn, hdr);
}
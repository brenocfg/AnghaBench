#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int len; int /*<<< orphan*/  type; } ;
struct hvsi_query {TYPE_1__ hdr; int /*<<< orphan*/  verb; } ;
struct hvsi_priv {int /*<<< orphan*/  termno; int /*<<< orphan*/  seqno; scalar_t__ established; } ;

/* Variables and functions */
 int /*<<< orphan*/  VSV_SEND_VERSION_NUMBER ; 
 int /*<<< orphan*/  VS_QUERY_PACKET_HEADER ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hvsi_send_packet (struct hvsi_priv*,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hvsi_start_handshake(struct hvsi_priv *pv)
{
	struct hvsi_query q;

	/* Reset state */
	pv->established = 0;
	atomic_set(&pv->seqno, 0);

	pr_devel("HVSI@%x: Handshaking started\n", pv->termno);

	/* Send version query */
	q.hdr.type = VS_QUERY_PACKET_HEADER;
	q.hdr.len = sizeof(struct hvsi_query);
	q.verb = cpu_to_be16(VSV_SEND_VERSION_NUMBER);
	hvsi_send_packet(pv, &q.hdr);
}
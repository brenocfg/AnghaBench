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
struct sctp_chunk {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_orphan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_clear_owner_w(struct sctp_chunk *chunk)
{
	skb_orphan(chunk->skb);
}
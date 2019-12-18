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
struct sctp_chunk {int /*<<< orphan*/  auth_chunk; int /*<<< orphan*/  skb; int /*<<< orphan*/  transmitted_list; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_DEC (struct sctp_chunk*) ; 
 int /*<<< orphan*/  consume_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sctp_chunk*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_chunk_cachep ; 

__attribute__((used)) static void sctp_chunk_destroy(struct sctp_chunk *chunk)
{
	BUG_ON(!list_empty(&chunk->list));
	list_del_init(&chunk->transmitted_list);

	consume_skb(chunk->skb);
	consume_skb(chunk->auth_chunk);

	SCTP_DBG_OBJCNT_DEC(chunk);
	kmem_cache_free(sctp_chunk_cachep, chunk);
}
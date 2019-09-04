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
struct ef4_tx_queue {int dummy; } ;
struct ef4_tx_buffer {int /*<<< orphan*/  unmap_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_BUG_ON_PARANOID (int /*<<< orphan*/ ) ; 
 struct ef4_tx_buffer* __ef4_tx_queue_get_insert_buffer (struct ef4_tx_queue const*) ; 

__attribute__((used)) static inline struct ef4_tx_buffer *
ef4_tx_queue_get_insert_buffer(const struct ef4_tx_queue *tx_queue)
{
	struct ef4_tx_buffer *buffer =
		__ef4_tx_queue_get_insert_buffer(tx_queue);

	EF4_BUG_ON_PARANOID(buffer->len);
	EF4_BUG_ON_PARANOID(buffer->flags);
	EF4_BUG_ON_PARANOID(buffer->unmap_len);

	return buffer;
}
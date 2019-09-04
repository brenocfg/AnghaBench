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
struct snd_seq_client {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 scalar_t__ snd_seq_total_cells (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int snd_seq_write_pool_allocated(struct snd_seq_client *client)
{
	return snd_seq_total_cells(client->pool) > 0;
}
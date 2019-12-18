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
struct PktStreamStat {int pkt_block; scalar_t__ final_done; } ;
typedef  int /*<<< orphan*/  PushFilter ;

/* Variables and functions */
 int STREAM_BLOCK_SHIFT ; 
 struct PktStreamStat* px_alloc (int) ; 

__attribute__((used)) static int
pkt_stream_init(PushFilter *next, void *init_arg, void **priv_p)
{
	struct PktStreamStat *st;

	st = px_alloc(sizeof(*st));
	st->final_done = 0;
	st->pkt_block = 1 << STREAM_BLOCK_SHIFT;
	*priv_p = st;

	return st->pkt_block;
}
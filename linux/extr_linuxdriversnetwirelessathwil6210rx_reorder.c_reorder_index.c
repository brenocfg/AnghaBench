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
typedef  int /*<<< orphan*/  u16 ;
struct wil_tid_ampdu_rx {int buf_size; int /*<<< orphan*/  ssn; } ;

/* Variables and functions */
 int seq_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int reorder_index(struct wil_tid_ampdu_rx *r, u16 seq)
{
	return seq_sub(seq, r->ssn) % r->buf_size;
}
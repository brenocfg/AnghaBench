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
typedef  int /*<<< orphan*/  u32 ;
struct hlist_head {int dummy; } ;
struct bpf_htab {int dummy; } ;
struct TYPE_2__ {struct hlist_head head; } ;

/* Variables and functions */
 TYPE_1__* __select_bucket (struct bpf_htab*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hlist_head *select_bucket(struct bpf_htab *htab, u32 hash)
{
	return &__select_bucket(htab, hash)->head;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct sctp_hash_cmp_arg {int /*<<< orphan*/  paddr; int /*<<< orphan*/  lport; int /*<<< orphan*/  net; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_hashfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __u32 sctp_hash_key(const void *data, u32 len, u32 seed)
{
	const struct sctp_hash_cmp_arg *x = data;

	return sctp_hashfn(x->net, x->lport, x->paddr, seed);
}
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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  SUB48 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TO_SIGNED48 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline s64 dccp_delta_seqno(const u64 seqno1, const u64 seqno2)
{
	u64 delta = SUB48(seqno2, seqno1);

	return TO_SIGNED48(delta);
}
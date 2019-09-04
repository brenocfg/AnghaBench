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
typedef  int /*<<< orphan*/  uint32_t ;
struct rseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_rseq ; 
 int syscall (int /*<<< orphan*/ ,struct rseq volatile*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sys_rseq(volatile struct rseq *rseq_abi, uint32_t rseq_len,
		    int flags, uint32_t sig)
{
	return syscall(__NR_rseq, rseq_abi, rseq_len, flags, sig);
}
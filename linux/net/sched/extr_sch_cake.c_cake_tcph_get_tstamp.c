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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tcphdr {int dummy; } ;

/* Variables and functions */
 int TCPOLEN_TIMESTAMP ; 
 int /*<<< orphan*/  TCPOPT_TIMESTAMP ; 
 int /*<<< orphan*/ * cake_get_tcpopt (struct tcphdr const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  get_unaligned_be32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void cake_tcph_get_tstamp(const struct tcphdr *tcph,
				 u32 *tsval, u32 *tsecr)
{
	const u8 *ptr;
	int opsize;

	ptr = cake_get_tcpopt(tcph, TCPOPT_TIMESTAMP, &opsize);

	if (ptr && opsize == TCPOLEN_TIMESTAMP) {
		*tsval = get_unaligned_be32(ptr);
		*tsecr = get_unaligned_be32(ptr + 4);
	}
}
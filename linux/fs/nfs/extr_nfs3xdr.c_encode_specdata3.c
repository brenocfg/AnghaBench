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
struct xdr_stream {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  void* __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/  const) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void** xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_specdata3(struct xdr_stream *xdr, const dev_t rdev)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, 8);
	*p++ = cpu_to_be32(MAJOR(rdev));
	*p = cpu_to_be32(MINOR(rdev));
}
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
struct nsm_args {int /*<<< orphan*/  proc; int /*<<< orphan*/  vers; int /*<<< orphan*/  prog; int /*<<< orphan*/  nodename; } ;
typedef  void* __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nsm_string (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 void** xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_my_id(struct xdr_stream *xdr, const struct nsm_args *argp)
{
	__be32 *p;

	encode_nsm_string(xdr, argp->nodename);
	p = xdr_reserve_space(xdr, 4 + 4 + 4);
	*p++ = cpu_to_be32(argp->prog);
	*p++ = cpu_to_be32(argp->vers);
	*p = cpu_to_be32(argp->proc);
}
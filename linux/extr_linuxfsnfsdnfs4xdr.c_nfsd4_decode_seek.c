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
struct nfsd4_seek {int /*<<< orphan*/  seek_whence; int /*<<< orphan*/  seek_offset; int /*<<< orphan*/  seek_stateid; } ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd4_decode_stateid (struct nfsd4_compoundargs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p ; 
 scalar_t__ status ; 
 int /*<<< orphan*/  xdr_decode_hyper (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_decode_seek(struct nfsd4_compoundargs *argp, struct nfsd4_seek *seek)
{
	DECODE_HEAD;

	status = nfsd4_decode_stateid(argp, &seek->seek_stateid);
	if (status)
		return status;

	READ_BUF(8 + 4);
	p = xdr_decode_hyper(p, &seek->seek_offset);
	seek->seek_whence = be32_to_cpup(p);

	DECODE_TAIL;
}
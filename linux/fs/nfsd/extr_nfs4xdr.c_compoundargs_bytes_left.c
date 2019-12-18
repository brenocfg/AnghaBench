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
struct nfsd4_compoundargs {unsigned int pagelen; scalar_t__ p; scalar_t__ end; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int compoundargs_bytes_left(struct nfsd4_compoundargs *argp)
{
	unsigned int this = (char *)argp->end - (char *)argp->p;

	return this + argp->pagelen;
}
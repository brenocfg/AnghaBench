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
struct nfsd4_compoundargs {int pagelen; scalar_t__ p; scalar_t__ end; int /*<<< orphan*/ * pagelist; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ XDR_QUADLEN (int) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void next_decode_page(struct nfsd4_compoundargs *argp)
{
	argp->p = page_address(argp->pagelist[0]);
	argp->pagelist++;
	if (argp->pagelen < PAGE_SIZE) {
		argp->end = argp->p + XDR_QUADLEN(argp->pagelen);
		argp->pagelen = 0;
	} else {
		argp->end = argp->p + (PAGE_SIZE>>2);
		argp->pagelen -= PAGE_SIZE;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct nfsd4_compoundargs {char* end; char* p; scalar_t__ pagelen; int tail; char* tmp; char* tmpp; TYPE_2__* rqstp; } ;
struct kvec {unsigned int iov_len; char* iov_base; } ;
typedef  char __be32 ;
struct TYPE_3__ {struct kvec* tail; } ;
struct TYPE_4__ {TYPE_1__ rq_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ XDR_QUADLEN (unsigned int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  next_decode_page (struct nfsd4_compoundargs*) ; 

__attribute__((used)) static __be32 *read_buf(struct nfsd4_compoundargs *argp, u32 nbytes)
{
	/* We want more bytes than seem to be available.
	 * Maybe we need a new page, maybe we have just run out
	 */
	unsigned int avail = (char *)argp->end - (char *)argp->p;
	__be32 *p;

	if (argp->pagelen == 0) {
		struct kvec *vec = &argp->rqstp->rq_arg.tail[0];

		if (!argp->tail) {
			argp->tail = true;
			avail = vec->iov_len;
			argp->p = vec->iov_base;
			argp->end = vec->iov_base + avail;
		}

		if (avail < nbytes)
			return NULL;

		p = argp->p;
		argp->p += XDR_QUADLEN(nbytes);
		return p;
	}

	if (avail + argp->pagelen < nbytes)
		return NULL;
	if (avail + PAGE_SIZE < nbytes) /* need more than a page !! */
		return NULL;
	/* ok, we can do it with the current plus the next page */
	if (nbytes <= sizeof(argp->tmp))
		p = argp->tmp;
	else {
		kfree(argp->tmpp);
		p = argp->tmpp = kmalloc(nbytes, GFP_KERNEL);
		if (!p)
			return NULL;
		
	}
	/*
	 * The following memcpy is safe because read_buf is always
	 * called with nbytes > avail, and the two cases above both
	 * guarantee p points to at least nbytes bytes.
	 */
	memcpy(p, argp->p, avail);
	next_decode_page(argp);
	memcpy(((char*)p)+avail, argp->p, (nbytes - avail));
	argp->p += XDR_QUADLEN(nbytes - avail);
	return p;
}
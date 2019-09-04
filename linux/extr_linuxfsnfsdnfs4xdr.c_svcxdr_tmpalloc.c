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
typedef  scalar_t__ u32 ;
struct svcxdr_tmpbuf {void* buf; struct svcxdr_tmpbuf* next; } ;
struct nfsd4_compoundargs {struct svcxdr_tmpbuf* to_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct svcxdr_tmpbuf* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
svcxdr_tmpalloc(struct nfsd4_compoundargs *argp, u32 len)
{
	struct svcxdr_tmpbuf *tb;

	tb = kmalloc(sizeof(*tb) + len, GFP_KERNEL);
	if (!tb)
		return NULL;
	tb->next = argp->to_free;
	argp->to_free = tb;
	return tb->buf;
}
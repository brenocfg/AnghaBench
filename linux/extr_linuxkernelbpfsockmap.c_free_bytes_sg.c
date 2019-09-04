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
struct sock {int dummy; } ;
struct sk_msg_buff {int sg_start; struct scatterlist* sg_data; } ;
struct scatterlist {int length; scalar_t__ offset; scalar_t__ page_link; } ;

/* Variables and functions */
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,int) ; 

__attribute__((used)) static void free_bytes_sg(struct sock *sk, int bytes,
			  struct sk_msg_buff *md, bool charge)
{
	struct scatterlist *sg = md->sg_data;
	int i = md->sg_start, free;

	while (bytes && sg[i].length) {
		free = sg[i].length;
		if (bytes < free) {
			sg[i].length -= bytes;
			sg[i].offset += bytes;
			if (charge)
				sk_mem_uncharge(sk, bytes);
			break;
		}

		if (charge)
			sk_mem_uncharge(sk, sg[i].length);
		put_page(sg_page(&sg[i]));
		bytes -= sg[i].length;
		sg[i].length = 0;
		sg[i].page_link = 0;
		sg[i].offset = 0;
		i++;

		if (i == MAX_SKB_FRAGS)
			i = 0;
	}
	md->sg_start = i;
}
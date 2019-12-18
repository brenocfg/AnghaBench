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
typedef  int u8 ;
struct htable {int dummy; } ;
struct hbucket {int dummy; } ;

/* Variables and functions */
 size_t jhash_size (int) ; 

__attribute__((used)) static size_t
htable_size(u8 hbits)
{
	size_t hsize;

	/* We must fit both into u32 in jhash and size_t */
	if (hbits > 31)
		return 0;
	hsize = jhash_size(hbits);
	if ((((size_t)-1) - sizeof(struct htable)) / sizeof(struct hbucket *)
	    < hsize)
		return 0;

	return hsize * sizeof(struct hbucket *) + sizeof(struct htable);
}
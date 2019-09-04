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
typedef  unsigned long u32 ;
struct hashtab {int size; } ;
struct filename_trans {unsigned long stype; unsigned long ttype; unsigned long tclass; unsigned char* name; } ;

/* Variables and functions */
 unsigned long partial_name_hash (unsigned char,unsigned long) ; 

__attribute__((used)) static u32 filenametr_hash(struct hashtab *h, const void *k)
{
	const struct filename_trans *ft = k;
	unsigned long hash;
	unsigned int byte_num;
	unsigned char focus;

	hash = ft->stype ^ ft->ttype ^ ft->tclass;

	byte_num = 0;
	while ((focus = ft->name[byte_num++]))
		hash = partial_name_hash(focus, hash);
	return hash & (h->size - 1);
}
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
struct key_vector {unsigned char slen; } ;

/* Variables and functions */
 struct key_vector* node_parent (struct key_vector*) ; 

__attribute__((used)) static void node_push_suffix(struct key_vector *tn, unsigned char slen)
{
	while (tn->slen < slen) {
		tn->slen = slen;
		tn = node_parent(tn);
	}
}
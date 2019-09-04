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
typedef  int uint8_t ;
struct ip6_t {int next_header; } ;
struct ip6_srh_t {int type; } ;
struct __sk_buff {scalar_t__ data; scalar_t__ data_end; } ;

/* Variables and functions */
 void* cursor_advance (void*,int) ; 

__attribute__((always_inline)) struct ip6_srh_t *get_srh(struct __sk_buff *skb)
{
	void *cursor, *data_end;
	struct ip6_srh_t *srh;
	struct ip6_t *ip;
	uint8_t *ipver;

	data_end = (void *)(long)skb->data_end;
	cursor = (void *)(long)skb->data;
	ipver = (uint8_t *)cursor;

	if ((void *)ipver + sizeof(*ipver) > data_end)
		return NULL;

	if ((*ipver >> 4) != 6)
		return NULL;

	ip = cursor_advance(cursor, sizeof(*ip));
	if ((void *)ip + sizeof(*ip) > data_end)
		return NULL;

	if (ip->next_header != 43)
		return NULL;

	srh = cursor_advance(cursor, sizeof(*srh));
	if ((void *)srh + sizeof(*srh) > data_end)
		return NULL;

	if (srh->type != 4)
		return NULL;

	return srh;
}
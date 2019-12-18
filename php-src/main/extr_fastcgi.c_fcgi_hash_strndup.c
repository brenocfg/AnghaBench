#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* data; } ;
typedef  TYPE_1__ fcgi_hash ;
struct TYPE_5__ {scalar_t__ pos; scalar_t__ end; scalar_t__ data; struct TYPE_5__* next; } ;
typedef  TYPE_2__ fcgi_data_seg ;

/* Variables and functions */
 unsigned int FCGI_HASH_SEG_SIZE ; 
 scalar_t__ UNEXPECTED (int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 

__attribute__((used)) static inline char* fcgi_hash_strndup(fcgi_hash *h, char *str, unsigned int str_len)
{
	char *ret;

	if (UNEXPECTED(h->data->pos + str_len + 1 >= h->data->end)) {
		unsigned int seg_size = (str_len + 1 > FCGI_HASH_SEG_SIZE) ? str_len + 1 : FCGI_HASH_SEG_SIZE;
		fcgi_data_seg *p = (fcgi_data_seg*)malloc(sizeof(fcgi_data_seg) - 1 + seg_size);

		p->pos = p->data;
		p->end = p->pos + seg_size;
		p->next = h->data;
		h->data = p;
	}
	ret = h->data->pos;
	memcpy(ret, str, str_len);
	ret[str_len] = 0;
	h->data->pos += str_len + 1;
	return ret;
}
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
struct netbuf {size_t len; size_t maxlen; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/ * mem_alloc (size_t) ; 
 int /*<<< orphan*/  mem_free (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

struct netbuf *
__rpc_set_netbuf(struct netbuf *nb, const void *ptr, size_t len)
{
	if (nb->len != len) {
		if (nb->len)
			mem_free(nb->buf, nb->len);
		nb->buf = mem_alloc(len);
		if (nb->buf == NULL)
			return NULL;

		nb->maxlen = nb->len = len;
	}
	memcpy(nb->buf, ptr, len);
	return nb;
}
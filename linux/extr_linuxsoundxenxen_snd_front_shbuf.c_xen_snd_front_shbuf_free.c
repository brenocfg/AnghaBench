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
struct xen_snd_front_shbuf {scalar_t__* grefs; int num_grefs; scalar_t__* directory; int /*<<< orphan*/  buffer_sz; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 scalar_t__ GRANT_INVALID_REF ; 
 int /*<<< orphan*/  free_pages_exact (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access (scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  xen_snd_front_shbuf_clear (struct xen_snd_front_shbuf*) ; 

void xen_snd_front_shbuf_free(struct xen_snd_front_shbuf *buf)
{
	int i;

	if (buf->grefs) {
		for (i = 0; i < buf->num_grefs; i++)
			if (buf->grefs[i] != GRANT_INVALID_REF)
				gnttab_end_foreign_access(buf->grefs[i],
							  0, 0UL);
		kfree(buf->grefs);
	}
	kfree(buf->directory);
	free_pages_exact(buf->buffer, buf->buffer_sz);
	xen_snd_front_shbuf_clear(buf);
}
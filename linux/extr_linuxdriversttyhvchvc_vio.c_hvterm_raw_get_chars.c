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
typedef  size_t uint32_t ;
struct hvterm_priv {unsigned long left; size_t offset; char* buf; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  termno; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 unsigned long hvc_get_chars (int /*<<< orphan*/ ,char*,int) ; 
 struct hvterm_priv** hvterm_privs ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,unsigned long) ; 
 int min (int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hvterm_raw_get_chars(uint32_t vtermno, char *buf, int count)
{
	struct hvterm_priv *pv = hvterm_privs[vtermno];
	unsigned long i;
	unsigned long flags;
	int got;

	if (WARN_ON(!pv))
		return 0;

	spin_lock_irqsave(&pv->buf_lock, flags);

	if (pv->left == 0) {
		pv->offset = 0;
		pv->left = hvc_get_chars(pv->termno, pv->buf, count);

		/*
		 * Work around a HV bug where it gives us a null
		 * after every \r.  -- paulus
		 */
		for (i = 1; i < pv->left; ++i) {
			if (pv->buf[i] == 0 && pv->buf[i-1] == '\r') {
				--pv->left;
				if (i < pv->left) {
					memmove(&pv->buf[i], &pv->buf[i+1],
						pv->left - i);
				}
			}
		}
	}

	got = min(count, pv->left);
	memcpy(buf, &pv->buf[pv->offset], got);
	pv->offset += got;
	pv->left -= got;

	spin_unlock_irqrestore(&pv->buf_lock, flags);

	return got;
}
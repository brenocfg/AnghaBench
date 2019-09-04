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
struct fscache_cookie {int aux_len; int /*<<< orphan*/  flags; void* aux; void* inline_aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE_COOKIE_AUX_UPDATED ; 
 scalar_t__ memcmp (void*,void const*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
void fscache_update_aux(struct fscache_cookie *cookie, const void *aux_data)
{
	void *p;

	if (!aux_data)
		return;
	if (cookie->aux_len <= sizeof(cookie->inline_aux))
		p = cookie->inline_aux;
	else
		p = cookie->aux;

	if (memcmp(p, aux_data, cookie->aux_len) != 0) {
		memcpy(p, aux_data, cookie->aux_len);
		set_bit(FSCACHE_COOKIE_AUX_UPDATED, &cookie->flags);
	}
}
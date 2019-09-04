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
struct svc_sock {unsigned int sk_datalen; scalar_t__ sk_tcplen; int /*<<< orphan*/ ** sk_pages; } ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void svc_tcp_clear_pages(struct svc_sock *svsk)
{
	unsigned int i, len, npages;

	if (svsk->sk_datalen == 0)
		goto out;
	len = svsk->sk_datalen;
	npages = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	for (i = 0; i < npages; i++) {
		if (svsk->sk_pages[i] == NULL) {
			WARN_ON_ONCE(1);
			continue;
		}
		put_page(svsk->sk_pages[i]);
		svsk->sk_pages[i] = NULL;
	}
out:
	svsk->sk_tcplen = 0;
	svsk->sk_datalen = 0;
}
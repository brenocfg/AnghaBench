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
struct page {int dummy; } ;
struct dio_submit {size_t head; } ;
struct dio {struct page** pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct page* ERR_PTR (int) ; 
 scalar_t__ dio_pages_present (struct dio_submit*) ; 
 int dio_refill_pages (struct dio*,struct dio_submit*) ; 

__attribute__((used)) static inline struct page *dio_get_page(struct dio *dio,
					struct dio_submit *sdio)
{
	if (dio_pages_present(sdio) == 0) {
		int ret;

		ret = dio_refill_pages(dio, sdio);
		if (ret)
			return ERR_PTR(ret);
		BUG_ON(dio_pages_present(sdio) == 0);
	}
	return dio->pages[sdio->head];
}
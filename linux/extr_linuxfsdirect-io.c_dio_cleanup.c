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
struct dio_submit {scalar_t__ head; scalar_t__ tail; } ;
struct dio {int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dio_cleanup(struct dio *dio, struct dio_submit *sdio)
{
	while (sdio->head < sdio->tail)
		put_page(dio->pages[sdio->head++]);
}
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
struct dio_submit {int tail; int head; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned dio_pages_present(struct dio_submit *sdio)
{
	return sdio->tail - sdio->head;
}
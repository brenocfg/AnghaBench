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
struct spi_qup {unsigned int n_words; unsigned int w_size; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int spi_qup_len(struct spi_qup *controller)
{
	return controller->n_words * controller->w_size;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int fragment_size; } ;
struct wm_adsp_compr {TYPE_1__ size; } ;

/* Variables and functions */
 unsigned int WM_ADSP_DATA_WORD_SIZE ; 

__attribute__((used)) static inline unsigned int wm_adsp_compr_frag_words(struct wm_adsp_compr *compr)
{
	return compr->size.fragment_size / WM_ADSP_DATA_WORD_SIZE;
}
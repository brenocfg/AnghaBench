#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int const pos; int const size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ lzma_dict ;

/* Variables and functions */

__attribute__((used)) static inline uint8_t
dict_get(const lzma_dict *const dict, const uint32_t distance)
{
	return dict->buf[dict->pos - distance - 1
			+ (distance < dict->pos ? 0 : dict->size)];
}
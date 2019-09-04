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
typedef  int /*<<< orphan*/  u8 ;
struct soc_tplg {TYPE_1__* fw; int /*<<< orphan*/ * hdr_pos; } ;
struct TYPE_2__ {int size; int /*<<< orphan*/  const* data; } ;

/* Variables and functions */

__attribute__((used)) static inline int soc_tplg_is_eof(struct soc_tplg *tplg)
{
	const u8 *end = tplg->hdr_pos;

	if (end >= tplg->fw->data + tplg->fw->size)
		return 1;
	return 0;
}
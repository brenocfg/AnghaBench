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
struct soc_tplg {int /*<<< orphan*/  dev; TYPE_1__* fw; int /*<<< orphan*/ * pos; } ;
struct TYPE_2__ {int size; int /*<<< orphan*/  const* data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static int soc_tplg_check_elem_count(struct soc_tplg *tplg, size_t elem_size,
	unsigned int count, size_t bytes, const char *elem_type)
{
	const u8 *end = tplg->pos + elem_size * count;

	if (end > tplg->fw->data + tplg->fw->size) {
		dev_err(tplg->dev, "ASoC: %s overflow end of data\n",
			elem_type);
		return -EINVAL;
	}

	/* check there is enough room in chunk for control.
	   extra bytes at the end of control are for vendor data here  */
	if (elem_size * count > bytes) {
		dev_err(tplg->dev,
			"ASoC: %s count %d of size %zu is bigger than chunk %zu\n",
			elem_type, count, elem_size, bytes);
		return -EINVAL;
	}

	return 0;
}
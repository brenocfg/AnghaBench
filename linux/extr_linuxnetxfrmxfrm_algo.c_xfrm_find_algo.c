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
struct xfrm_algo_list {int entries; int /*<<< orphan*/  mask; int /*<<< orphan*/  type; struct xfrm_algo_desc* algs; } ;
struct xfrm_algo_desc {int available; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int crypto_has_alg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfrm_algo_desc *xfrm_find_algo(
	const struct xfrm_algo_list *algo_list,
	int match(const struct xfrm_algo_desc *entry, const void *data),
	const void *data, int probe)
{
	struct xfrm_algo_desc *list = algo_list->algs;
	int i, status;

	for (i = 0; i < algo_list->entries; i++) {
		if (!match(list + i, data))
			continue;

		if (list[i].available)
			return &list[i];

		if (!probe)
			break;

		status = crypto_has_alg(list[i].name, algo_list->type,
					algo_list->mask);
		if (!status)
			break;

		list[i].available = status;
		return &list[i];
	}
	return NULL;
}
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
struct list_head {int dummy; } ;
struct heuristic_ws {struct list_head list; void* bucket_b; void* bucket; int /*<<< orphan*/  sample; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUCKET_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct list_head* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  MAX_SAMPLE_SIZE ; 
 int /*<<< orphan*/  free_heuristic_ws (struct list_head*) ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct heuristic_ws* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct list_head *alloc_heuristic_ws(unsigned int level)
{
	struct heuristic_ws *ws;

	ws = kzalloc(sizeof(*ws), GFP_KERNEL);
	if (!ws)
		return ERR_PTR(-ENOMEM);

	ws->sample = kvmalloc(MAX_SAMPLE_SIZE, GFP_KERNEL);
	if (!ws->sample)
		goto fail;

	ws->bucket = kcalloc(BUCKET_SIZE, sizeof(*ws->bucket), GFP_KERNEL);
	if (!ws->bucket)
		goto fail;

	ws->bucket_b = kcalloc(BUCKET_SIZE, sizeof(*ws->bucket_b), GFP_KERNEL);
	if (!ws->bucket_b)
		goto fail;

	INIT_LIST_HEAD(&ws->list);
	return &ws->list;
fail:
	free_heuristic_ws(&ws->list);
	return ERR_PTR(-ENOMEM);
}
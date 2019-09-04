#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int buf_count; int /*<<< orphan*/  entry_list; } ;
struct TYPE_4__ {TYPE_1__ init_pool; } ;
struct qeth_card {TYPE_2__ qdio; } ;
struct qeth_buffer_pool_entry {int /*<<< orphan*/  init_list; void** elements; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int QETH_MAX_BUFFER_ELEMENTS (struct qeth_card*) ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct qeth_buffer_pool_entry*) ; 
 struct qeth_buffer_pool_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_free_buffer_pool (struct qeth_card*) ; 

__attribute__((used)) static int qeth_alloc_buffer_pool(struct qeth_card *card)
{
	struct qeth_buffer_pool_entry *pool_entry;
	void *ptr;
	int i, j;

	QETH_CARD_TEXT(card, 5, "alocpool");
	for (i = 0; i < card->qdio.init_pool.buf_count; ++i) {
		pool_entry = kzalloc(sizeof(*pool_entry), GFP_KERNEL);
		if (!pool_entry) {
			qeth_free_buffer_pool(card);
			return -ENOMEM;
		}
		for (j = 0; j < QETH_MAX_BUFFER_ELEMENTS(card); ++j) {
			ptr = (void *) __get_free_page(GFP_KERNEL);
			if (!ptr) {
				while (j > 0)
					free_page((unsigned long)
						  pool_entry->elements[--j]);
				kfree(pool_entry);
				qeth_free_buffer_pool(card);
				return -ENOMEM;
			}
			pool_entry->elements[j] = ptr;
		}
		list_add(&pool_entry->init_list,
			 &card->qdio.init_pool.entry_list);
	}
	return 0;
}
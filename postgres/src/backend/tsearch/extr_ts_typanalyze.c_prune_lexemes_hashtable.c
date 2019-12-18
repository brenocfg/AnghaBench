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
struct TYPE_3__ {char* lexeme; } ;
struct TYPE_4__ {int frequency; int delta; TYPE_1__ key; } ;
typedef  TYPE_2__ TrackItem ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * hash_search (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static void
prune_lexemes_hashtable(HTAB *lexemes_tab, int b_current)
{
	HASH_SEQ_STATUS scan_status;
	TrackItem  *item;

	hash_seq_init(&scan_status, lexemes_tab);
	while ((item = (TrackItem *) hash_seq_search(&scan_status)) != NULL)
	{
		if (item->frequency + item->delta <= b_current)
		{
			char	   *lexeme = item->key.lexeme;

			if (hash_search(lexemes_tab, (const void *) &item->key,
							HASH_REMOVE, NULL) == NULL)
				elog(ERROR, "hash table corrupted");
			pfree(lexeme);
		}
	}
}
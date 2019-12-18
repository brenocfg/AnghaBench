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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int /*<<< orphan*/  NFSD_FILE_LAUNDRETTE_NOFLUSH ; 
 int /*<<< orphan*/  NFSD_FILE_LRU_RESCAN ; 
 int /*<<< orphan*/  flush_delayed_fput () ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lru_walk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_file_lru ; 
 int /*<<< orphan*/  nfsd_file_lru_cb ; 
 int /*<<< orphan*/  nfsd_file_lru_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_file_lru_flags ; 
 int /*<<< orphan*/  nfsd_file_schedule_laundrette (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfsd_file_delayed_close(struct work_struct *work)
{
	LIST_HEAD(head);

	list_lru_walk(&nfsd_file_lru, nfsd_file_lru_cb, &head, LONG_MAX);

	if (test_and_clear_bit(NFSD_FILE_LRU_RESCAN, &nfsd_file_lru_flags))
		nfsd_file_schedule_laundrette(NFSD_FILE_LAUNDRETTE_NOFLUSH);

	if (!list_empty(&head)) {
		nfsd_file_lru_dispose(&head);
		flush_delayed_fput();
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ value_len; } ;
struct TYPE_11__ {TYPE_1__ base; } ;
struct TYPE_10__ {int fd; TYPE_3__ tmpkv; int /*<<< orphan*/  dir; int /*<<< orphan*/  ndump; int /*<<< orphan*/  ht; int /*<<< orphan*/  ns; int /*<<< orphan*/  path; int /*<<< orphan*/  name; scalar_t__ refs; scalar_t__ lock; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ Sdb ;

/* Variables and functions */
 int /*<<< orphan*/  cdb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ls_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdb_hook_free (TYPE_2__*) ; 
 int /*<<< orphan*/  sdb_ht_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_journal_close (TYPE_2__*) ; 
 int /*<<< orphan*/  sdb_lock_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_ns_free (TYPE_2__*) ; 
 int /*<<< orphan*/  sdb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdbkv_value (TYPE_3__*) ; 

__attribute__((used)) static void sdb_fini(Sdb* s, int donull) {
	if (!s) {
		return;
	}
	sdb_hook_free (s);
	cdb_free (&s->db);
	if (s->lock) {
		sdb_unlock (sdb_lock_file (s->dir));
	}
	sdb_ns_free (s);
	s->refs = 0;
	free (s->name);
	free (s->path);
	ls_free (s->ns);
	sdb_ht_free (s->ht);
	sdb_journal_close (s);
	if (s->fd != -1) {
		close (s->fd);
		s->fd = -1;
	}
	free (s->ndump);
	free (s->dir);
	free (sdbkv_value (&s->tmpkv));
	s->tmpkv.base.value_len = 0;
	if (donull) {
		memset (s, 0, sizeof (Sdb));
	}
}
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
struct bsd_db {scalar_t__ clear_count; scalar_t__ seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  bsd_clear (struct bsd_db*) ; 

__attribute__((used)) static void bsd_reset (void *state)
  {
    struct bsd_db *db = (struct bsd_db *) state;

    bsd_clear(db);

    db->seqno       = 0;
    db->clear_count = 0;
  }
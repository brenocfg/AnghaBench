#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_4__ {int /*<<< orphan*/  h_buffer_credits; int /*<<< orphan*/  h_reserved; int /*<<< orphan*/ * h_journal; } ;
typedef  TYPE_1__ handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  jbd2_free_handle (TYPE_1__*) ; 
 int /*<<< orphan*/  sub_reserved_credits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void jbd2_journal_free_reserved(handle_t *handle)
{
	journal_t *journal = handle->h_journal;

	WARN_ON(!handle->h_reserved);
	sub_reserved_credits(journal, handle->h_buffer_credits);
	jbd2_free_handle(handle);
}
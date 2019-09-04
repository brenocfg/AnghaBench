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
struct buffer_st {int /*<<< orphan*/ * data; int /*<<< orphan*/ * ptr; scalar_t__ offset; scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 

void buffer_delete(struct buffer_st *b)
{
  efree(b->data);
  b->length = 0;
  b->offset = 0;
  b->ptr = NULL;
  b->data = NULL;
}
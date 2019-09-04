#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* context; } ;
struct TYPE_8__ {int /*<<< orphan*/ * str; } ;
struct TYPE_7__ {scalar_t__ grep; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf_len; int /*<<< orphan*/ * buf; } ;
struct TYPE_6__ {TYPE_3__ grep; int /*<<< orphan*/  buffer_sz; int /*<<< orphan*/  buffer_len; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_2__ RConsStack ;
typedef  int /*<<< orphan*/  RConsGrep ;

/* Variables and functions */
 TYPE_5__ I ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,scalar_t__,int) ; 

__attribute__((used)) static void cons_stack_load(RConsStack *data, bool free_current) {
	if (free_current) {
		free (I.context->buffer);
	}
	I.context->buffer = data->buf;
	data->buf = NULL;
	I.context->buffer_len = data->buf_len;
	I.context->buffer_sz = data->buf_size;

	if (data->grep) {
		free (I.context->grep.str);
		memcpy (&I.context->grep, data->grep, sizeof (RConsGrep));
	}
}
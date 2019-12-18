#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_3__ {int /*<<< orphan*/ * insn; int /*<<< orphan*/ * head; int /*<<< orphan*/  f; scalar_t__ length; scalar_t__ status; int /*<<< orphan*/  stream; int /*<<< orphan*/  syntax; } ;
typedef  TYPE_1__ tms320_dasm_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void init_dasm(tms320_dasm_t * dasm, const ut8 * stream, int len)
{
	strcpy(dasm->syntax, "invalid");
	memcpy(dasm->stream, stream, min(sizeof(dasm->stream), len));

	dasm->status = 0;
	dasm->length = 0;

	memset(&dasm->f, 0, sizeof(dasm->f));

	dasm->head = NULL;
	dasm->insn = NULL;
}
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
typedef  int /*<<< orphan*/  QueryOperand ;
typedef  int /*<<< orphan*/  GinChkVal ;
typedef  int /*<<< orphan*/  ExecPhraseData ;

/* Variables and functions */
 scalar_t__ GIN_FALSE ; 
 scalar_t__ checkcondition_gin_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
checkcondition_gin(void *checkval, QueryOperand *val, ExecPhraseData *data)
{
	return checkcondition_gin_internal((GinChkVal *) checkval,
									   val,
									   data) != GIN_FALSE;
}
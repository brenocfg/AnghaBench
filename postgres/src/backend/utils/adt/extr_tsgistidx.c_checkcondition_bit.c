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
struct TYPE_3__ {int /*<<< orphan*/  valcrc; scalar_t__ prefix; } ;
typedef  TYPE_1__ QueryOperand ;
typedef  int /*<<< orphan*/  ExecPhraseData ;

/* Variables and functions */
 int GETBIT (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASHVAL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
checkcondition_bit(void *checkval, QueryOperand *val, ExecPhraseData *data)
{
	/*
	 * we are not able to find a prefix in signature tree
	 */
	if (val->prefix)
		return true;
	return GETBIT(checkval, HASHVAL(val->valcrc));
}